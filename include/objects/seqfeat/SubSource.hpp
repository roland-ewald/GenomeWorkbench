/* $Id: SubSource.hpp 599623 2020-01-03 20:13:09Z bollin $
 * ===========================================================================
 *
 *                            PUBLIC DOMAIN NOTICE
 *               National Center for Biotechnology Information
 *
 *  This software/database is a "United States Government Work" under the
 *  terms of the United States Copyright Act.  It was written as part of
 *  the author's official duties as a United States Government employee and
 *  thus cannot be copyrighted.  This software/database is freely available
 *  to the public for use. The National Library of Medicine and the U.S.
 *  Government have not placed any restriction on its use or reproduction.
 *
 *  Although all reasonable efforts have been taken to ensure the accuracy
 *  and reliability of the software and data, the NLM and the U.S.
 *  Government do not and cannot warrant the performance or results that
 *  may be obtained by using this software or data. The NLM and the U.S.
 *  Government disclaim all warranties, express or implied, including
 *  warranties of performance, merchantability or fitness for any particular
 *  purpose.
 *
 *  Please cite the author in any work or product based on this material.
 *
 * ===========================================================================
 *
 */

/// @SubSource.hpp
/// User-defined methods of the data storage class.
///
/// This file was originally generated by application DATATOOL
/// using the following specifications:
/// 'seqfeat.asn'.
///
/// New methods or data members can be added to it if needed.
/// See also: SubSource_.hpp


#ifndef OBJECTS_SEQFEAT_SUBSOURCE_HPP
#define OBJECTS_SEQFEAT_SUBSOURCE_HPP


// generated includes
#include <objects/seqfeat/SubSource_.hpp>

// generated classes


// other includes
#include <objects/general/Date.hpp>
#include <objects/general/Date_std.hpp>
#include <corelib/ncbitime.hpp>
#include <util/static_map.hpp>

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::
class CDate;
class CDate_std;
class CLatLonCountryId;
class CLatLonCountryMap;

/////////////////////////////////////////////////////////////////////////////
class NCBI_SEQFEAT_EXPORT CSubSource : public CSubSource_Base
{
    typedef CSubSource_Base Tparent;
public:
    // constructor
    CSubSource(void);
    CSubSource(TSubtype subtype, const TName& name);
    CSubSource(const string& subtype, const TName& name);

    // destructor
    ~CSubSource(void);

    void GetLabel(string* str) const;

    enum EVocabulary {
        eVocabulary_raw, // per ASN.1, except eSubtype_other <-> "note"
        eVocabulary_insdc // per GB/DDBJ/EMBL qualifier names
    };

    // convert subtype from string to enum.
    static TSubtype GetSubtypeValue(const string& str,
                                    EVocabulary vocabulary = eVocabulary_raw);

	// get name for subsource
    static string GetSubtypeName(CSubSource::TSubtype stype,
                                 EVocabulary vocabulary = eVocabulary_raw);

    // tests whether GetSubtypeName is expected to throw an exception
    static bool IsValidSubtypeName(const string& str,
                                   EVocabulary vocabulary = eVocabulary_raw);              

    static bool IsMultipleValuesAllowed(TSubtype);

    // identify whether subsource value should be blank
    static bool NeedsNoText (const TSubtype& subtype);

    // some subsources are discouraged and should not be offered to the user as an option
    static bool IsDiscouraged (const TSubtype subtype);

	// read collection date from string
    static CRef<CDate> DateFromCollectionDate (const string& str) THROWS((CException));

    static void IsCorrectDateFormat(const string& date_string, bool& bad_format, bool& in_future);
    typedef enum {
        eDateFormatFlag_ok = 0,
        eDateFormatFlag_bad_format = 1,
        eDateFormatFlag_in_future = 2,
        eDateFormatFlag_out_of_order = 4
    } EDateFormatFlag;
    static size_t CheckDateFormat(const string& date_string);

    static string GetCollectionDateProblem (const string& date_string);
    static bool IsCollectionDateAfterTime(const string& collection_date, time_t t, bool& bad_format);
    static bool IsCollectionDateAfterTime(const CDate& collection_date, time_t t);
    static bool IsCollectionDateAfterTime(const CDate& collection_date, CTime& ctime);

    static bool IsISOFormatTime(const string& orig_time, int& hour, int& min, int& sec, bool require_time_zone = true);
    static bool IsISOFormatDateOnly(const string& date);
    static bool IsISOFormatDate (const string& orig_date);
    static CRef<CDate> GetDateFromISODate(const string& orig_date);

    /// Determine whether day number could occur in month.
    /// @param day   The number of the day, 1-based [in]
    /// @param month The number of the month, 1-based [in]
    /// @param year  The number of the year, 1-based [in]
    static bool IsDayValueOkForMonth(int day, int month, int year);

    /// Attempt to fix the format of the date
    /// Returns a blank if the format of the date cannot be determined
    /// @param orig_date The original date [in]
    /// Rules:
    /// First, check to see if the string matches the ISO format (YYYY-MM-DD);
    /// if so then just return original string as this is valid.
    /// Second, try to split the string into tokens using the following delimiters:
    ///      * space
    ///      * comma (,)
    ///      * dash (-)
    ///      * slash (/)
    ///      * underscore (_)
    ///      * equals (=)
    ///      * period (.)
    /// If more than three tokens are generated, fail and return empty string.
    /// Of the tokens that are generated, look for a token that contains letters.
    /// If there is such a token, this token is assumed to be the month, and will
    /// be checked to see if it begins with any of the three-letter abbreviations
    /// for months (Jan, Feb, Mar, etc.). If so, the month is known. If none of 
    /// the abbreviations produce a match, fail and return an empty string. If 
    /// more than one token that contains letters is found, return an empty string.
    /// If there are no tokens that contain letters, try to determine which token is
    /// the month by eliminating tokens that would be year or day.
    /// Any token that is a number and has a value greater than 31 will be assumed
    /// to be the year. If there is more than one such token, return an empty string.
    /// After making this initial pass, try to guess the identities of the remaining tokens.
    /// Numbers between 1 and 12 could be considered months, if no month token containing
    /// letters was already identified. If two or more such tokens are found, the date is 
    /// ambiguous: return an empty string, unless one of these two conditions are met:
    ///   a) the numbers are equal, in which case ambiguity about placement is irrelevant
    ///   b) if one token is NOT zero-padded and less than 10, and the other is 
    ///      either 10 or more or IS zero-padded, then the token that is not padded and
    ///      less than 10 is the day, and the other is the year, to which we should add 2000
    /// If a number is between 1 and 31, it could be considered the day. If two such tokens
    /// are found, the date is ambiguous: return an empty string.
    /// If there is a number that cannot be the month or the day, assume that this is the
    /// year. If the year is less than 100, this may be a two-digit representation. If
    /// 2000 + the value is not in the future, use this as the year, otherwise use
    /// 1900 + the value for the year.
    /// If all tokens can be identified, arrange them in the output string in one of the 
    /// following formats:
    /// YYYY
    /// Mmm-YYYY
    /// DD-Mmm-YYYY

    static string FixDateFormat(const string& orig_date);
    static string FixDateFormat(const string& orig_date, bool month_first, bool& month_ambiguous);
    static void DetectDateFormat(const string& orig_date, bool& ambiguous, bool &day_first);
    static void IsCorrectLatLonFormat (string lat_lon, bool& format_correct, bool& precision_correct,
                                     bool& lat_in_range, bool& lon_in_range,
                                     double& lat_value, double& lon_value);
    static string FixLatLonFormat (string orig_lat_lon, bool guess = false);
    static string MakeLatLon(double lat_value, double lon_value, int lat_precision = 2, int lon_precision = 2);
    static string FixLatLonPrecision(const string& orig);

    enum ELatLonCountryErr {
        eLatLonCountryErr_None = 0,
        eLatLonCountryErr_Country,
        eLatLonCountryErr_State,
        eLatLonCountryErr_Water,
        eLatLonCountryErr_Value
    };
    
    static string ValidateLatLonCountry (const string& countryname, string& lat_lon, bool check_state, ELatLonCountryErr& errcode);

    static bool IsValidSexQualifierValue (const string& value);
    static string FixSexQualifierValue (const string& value);

    static bool IsAltitudeValid (const string& value);
    static string FixAltitude (const string& value);

    static bool IsPlasmidNameValid(const string& value, const string& taxname);
    static bool IsChromosomeNameValid(const string& value, const string& taxname);
    static bool IsLinkageGroupNameValid(const string& value, const string& taxname);
    static bool IsSegmentValid(const string& value);
    static bool IsEndogenousVirusNameValid(const string& value);


    static string FixDevStageCapitalization(const string& value);
    static string FixCellTypeCapitalization(const string& value);
    static string FixIsolationSourceCapitalization(const string& value);
    static string FixTissueTypeCapitalization(const string& value);
    static string FixLabHostCapitalization(const string& value);
    static string FixCapitalization(TSubtype subtype, const string& value);
    void FixCapitalization();

    static string AutoFix(TSubtype subtype, const string& value);
    void AutoFix();

    static bool HasCultureNotes(const string& value);
    static void RemoveCultureNotes(string& value, bool is_species_level = true);
    void RemoveCultureNotes(bool is_species_level = true);

    static string CheckCellLine(const string& cell_line, const string& organism);

private:
    // Prohibit copy constructor and assignment operator
    CSubSource(const CSubSource& value);
    CSubSource& operator=(const CSubSource& value);

    static string x_ParseDateRangeWithDelimiter(const string& orig_date, CTempString delim);
    static vector<string> x_GetDateTokens(const string& orig_date);
    static CLatLonCountryId * x_CalculateLatLonId(float lat_value, float lon_value, string country, string province);
    static bool x_IsFixableIsoDate(const string& orig_date);
    static string x_RemoveIsoTime(const string& orig_date);

    static int x_GetPrecision(const string& num_str);
    static string x_FormatWithPrecision(double val, int precision);

    static bool x_GenericRepliconNameValid(const string& value);
    static bool x_MeetsCommonChromosomeLinkageGroupPlasmidNameRules(const string& value, const string& taxname);

    // validation data read from external files
    static auto_ptr<CLatLonCountryMap> m_LatLonCountryMap;
    static auto_ptr<CLatLonCountryMap> m_LatLonWaterMap;

};

/////////////////// CSubSource inline methods

// constructor
inline
CSubSource::CSubSource(void)
{
}

inline
CSubSource::CSubSource(TSubtype subtype, const TName& name)
{
    SetSubtype(subtype);
    SetName(name);
}

inline
CSubSource::CSubSource(const string& subtype, const TName& name)
{
    SetSubtype(GetSubtypeValue(subtype));
    SetName(name);
}


/////////////////// end of CSubSource inline methods


// =============================================================================
//                 Country Names (legal values found in country subtype)
// =============================================================================


class NCBI_SEQFEAT_EXPORT CCountries
{
public:
    static bool IsValid(const string& country);
    static bool IsValid(const string& country, bool& is_miscapitalized);
    static bool WasValid(const string& country);
    static bool WasValid(const string& country, bool& is_miscapitalized);
    static string CapitalizeFirstLetterOfEveryWord (const string &phrase);
    static string WholeCountryFix(string country);
    static bool IsSubstringOfStringInList(const string& phrase, const string& country1, size_t pos1);
    static bool ContainsMultipleCountryNames (const string &phrase);
    static string GetCorrectedCountryCapitalization(const string& country);
    static string NewFixCountry (const string& input);
    static bool ChangeExtraColonsToCommas(string& country);
    static string CountryFixupItem(const string &input, bool capitalize_after_colon);
    typedef CStaticPairArrayMap<const char*, const char*, PCase_CStr> TCStringPairsMap;
private:
    static const string sm_Countries[];
    static const string sm_Former_Countries[];
    static void x_RemoveDelimitersFromEnds(string& val, bool except_paren = false);
    static vector<string> x_Tokenize(const string& val);
    static void x_FindCountryName(const TCStringPairsMap& fix_map, const vector<string>& countries, string& valid_country, string& orig_valid_country, bool& too_many_countries, bool& bad_cap);
};


// ==================== for validating lat-lon versus country ================

class CCountryLine;

class NCBI_SEQFEAT_EXPORT CCountryExtreme
{
public:
    CCountryExtreme (const string & country_name, int min_x, int min_y, int max_x, int max_y);
    ~CCountryExtreme (void);

    string GetCountry(void)         const { return m_CountryName; }
    string GetLevel0(void)         const { return m_Level0; }
    string GetLevel1(void)         const { return m_Level1; }
    int GetMinX(void)               const { return m_MinX; }
    int GetMinY(void)               const { return m_MinY; }
    int GetMaxX(void)               const { return m_MaxX; }
    int GetMaxY(void)               const { return m_MaxY; }
    int GetArea(void)               const { return m_Area; }
    void AddLine(const CCountryLine* line);
    bool SetMinX(int min_x);
    bool SetMinY(int min_y);
    bool SetMaxX(int max_x);
    bool SetMaxY(int max_y);
    bool DoesOverlap(const CCountryExtreme* other_block) const;
    bool PreferTo(const CCountryExtreme* other_block, const string country, const string province, const bool prefer_new) const;

private:
    string m_CountryName;
    string m_Level0;
    string m_Level1;
    int m_MinX;
    int m_MinY;
    int m_MaxX;
    int m_MaxY;
    int m_Area;
};


class CCountryLine
{
public:
    CCountryLine (const string & country_name, double y, double min_x, double max_x, double scale);
    ~CCountryLine (void);

    const string & GetCountry(void)            const { return m_CountryName; }
  double GetLat(void)                const { return m_Y / m_Scale; }
  double GetMinLon(void)             const { return m_MinX / m_Scale; }
  double GetMaxLon(void)             const { return m_MaxX / m_Scale; }
  int GetY(void)                  const { return m_Y; }
  int GetMinX(void)               const { return m_MinX; }
  int GetMaxX(void)               const { return m_MaxX; }

  static int ConvertLat(double y, double scale);
  static int ConvertLon(double x, double scale);

  void SetBlock (CCountryExtreme *block) { m_Block = block; }
  CCountryExtreme * GetBlock(void) const {return m_Block; }

private:
  int x_ConvertLat(double y);
  int x_ConvertLon(double x);

  CCountryExtreme *m_Block;
    string m_CountryName;
    int m_Y;
    int m_MinX;
    int m_MaxX;
  double m_Scale;
};


class NCBI_SEQFEAT_EXPORT CLatLonCountryId
{
public:
    CLatLonCountryId(float lat, float lon);
    ~CLatLonCountryId(void);

    float GetLat(void) const { return m_Lat; }
    void  SetLat(float lat) { m_Lat = lat; }
    float GetLon(void) const { return m_Lon; }
    void  SetLon(float lon) { m_Lon = lon; }
    string GetFullGuess(void) const { return m_FullGuess; }
    void  SetFullGuess(string guess) { m_FullGuess = guess; }
    string GetGuessCountry(void) const { return m_GuessCountry; }
    void  SetGuessCountry(string guess) { m_GuessCountry = guess; }
    string GetGuessProvince(void) const { return m_GuessProvince; }
    void  SetGuessProvince(string guess) { m_GuessProvince = guess; }
    string GetGuessWater(void) const { return m_GuessWater; }
    void  SetGuessWater(string guess) { m_GuessWater = guess; }
    string GetClosestFull(void) const { return m_ClosestFull; }
    void  SetClosestFull(string closest) { m_ClosestFull = closest; }
    string GetClosestCountry(void) const { return m_ClosestCountry; }
    void  SetClosestCountry(string closest) { m_ClosestCountry = closest; }
    string GetClosestProvince(void) const { return m_ClosestProvince; }
    void  SetClosestProvince(string closest) { m_ClosestProvince = closest; }
    string GetClosestWater(void) const { return m_ClosestWater; }
    void  SetClosestWater(string closest) { m_ClosestWater = closest; }
    string GetClaimedFull(void) const { return m_ClaimedFull; }
    void  SetClaimedFull(string claimed) { m_ClaimedFull = claimed; }

    int GetLandDistance(void) const { return m_LandDistance; }
    void SetLandDistance (int dist) { m_LandDistance = dist; }
    int GetWaterDistance(void) const { return m_WaterDistance; }
    void SetWaterDistance (int dist) { m_WaterDistance = dist; }
    int GetClaimedDistance(void) const { return m_ClaimedDistance; }
    void SetClaimedDistance (int dist) { m_ClaimedDistance = dist; }


    enum EClassificationFlags {
        fCountryMatch    = (1),
        fProvinceMatch   = (1 << 1),
        fWaterMatch      = (1 << 2), 
        fOverlap         = (1 << 3), 
        fCountryClosest  = (1 << 4), 
        fProvinceClosest = (1 << 5),
        fWaterClosest    = (1 << 6)
    };
    typedef int TClassificationFlags;    ///< Bitwise OR of "EClassificationFlags"

    CLatLonCountryId::TClassificationFlags Classify(string country, string province);


private:
  float  m_Lat;
  float  m_Lon;
  string m_FullGuess;
  string m_GuessCountry;
  string m_GuessProvince;
  string m_GuessWater;
  string m_ClosestFull;
  string m_ClosestCountry;
  string m_ClosestProvince;
  string m_ClosestWater;
  string m_ClaimedFull;
  int    m_LandDistance;
  int    m_WaterDistance;
  int    m_ClaimedDistance;
};

class NCBI_SEQFEAT_EXPORT CLatLonCountryMap
{
public:
    CLatLonCountryMap(bool is_water);
    ~CLatLonCountryMap(void);
    bool IsCountryInLatLon(const string& country, double lat, double lon);
    const CCountryExtreme * GuessRegionForLatLon(double lat, double lon,
                                            const string& country = kEmptyStr,
                                            const string& province = kEmptyStr);
    const CCountryExtreme * FindClosestToLatLon(double lat, double lon,
                                                double range, double& distance);
    bool IsClosestToLatLon(const string& country, double lat, double lon,
                           double range, double& distance);
    bool HaveLatLonForRegion(const string& country);
    bool DoCountryBoxesOverlap(const string& country1, const string& country2);
    const CCountryExtreme * IsNearLatLon(double lat, double lon, double range,
                                         double& distance,
                                         const string& country,
                                         const string& province = kEmptyStr);
    double GetScale (void) { return m_Scale; }
    static int AdjustAndRoundDistance (double distance, double scale);
    int AdjustAndRoundDistance (double distance);

    enum ELatLonAdjustFlags {
      fNone      = 0 ,
      fFlip      = 1 ,
      fNegateLat = (1 << 1),
      fNegateLon = (1 << 2),
    };
    typedef int TLatLonAdjustFlags;    ///< Bitwise OR of "ELatLonAdjustFlags"


private:
    void x_InitFromDefaultList(const char * const *list, int num);
    bool x_InitFromFile(const string& filename);
    static bool s_CompareTwoLinesByLatLonOnly(const CCountryLine* line1,
                                    const CCountryLine* line2);
    static bool s_CompareTwoLinesByCountry(const CCountryLine* line1,
                                    const CCountryLine* line2);
    static bool s_CompareTwoLinesByLatLonThenCountry(const CCountryLine* line1,
                                    const CCountryLine* line2);

    size_t x_GetLatStartIndex (int y);
    const CCountryExtreme * x_FindCountryExtreme (const string& country);


    typedef vector <CCountryLine *> TCountryLineList;
    typedef TCountryLineList::const_iterator TCountryLineList_iter; 

    TCountryLineList m_CountryLineList;
    TCountryLineList m_LatLonSortedList;
    double m_Scale;

    typedef vector <CCountryExtreme *> TCountryExtremeList;
    typedef TCountryExtremeList::const_iterator TCountryExtremeList_iter; 
    TCountryExtremeList m_CountryExtremes;


      static const string sm_BodiesOfWater[];



};

NCBI_SEQFEAT_EXPORT double ErrorDistance (
  double latA,
  double lonA,
  double scale);



END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE

#endif // OBJECTS_SEQFEAT_SUBSOURCE_HPP
/* Original file checksum: lines: 94, chars: 2578, CRC32: 1c534244 */