/* $Id: PluginMessage.hpp 14666 2007-07-09 13:40:22Z dicuccio $
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
 * Author:  .......
 *
 * File Description:
 *   .......
 *
 * Remark:
 *   This code was originally generated by application DATATOOL
 *   using specifications from the data definition file
 *   'plugin.asn'.
 */

#ifndef GUI_PLUGIN_PLUGINMESSAGE_HPP
#define GUI_PLUGIN_PLUGINMESSAGE_HPP

#include <corelib/ncbistre.hpp>
#include <gui/utils/reporter.hpp>

// generated includes
#include <gui/objects/PluginMessage_.hpp>

// generated classes

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::

class NCBI_GUIOBJECTS_EXPORT CPluginMessage : public CPluginMessage_Base
{
    typedef CPluginMessage_Base Tparent;
public:
    // constructor
    CPluginMessage(void);
    // destructor
    ~CPluginMessage(void);

    /// access a globally unique ID for this message
    typedef unsigned int        TId;
    TId GetId(void) const;

    /// generate a usable label for this message
    enum ELabelType {
        eType,
        eContent,
        eBoth,

        eDefault = eBoth
    };
    typedef int TFlags;
    void GetLabel(string* str, ELabelType type = eDefault, TFlags flags = 0) const;

    void             SetReporter(IReporter* reporter);
    IReporter*       SetReporter();
    const IReporter* GetReporter() const;

    /// clear all objects from the message
    enum EClearType {
        fClear_Request = 0x01,
        fClear_Reply   = 0x02,
        fClear_Both    = fClear_Request | fClear_Reply,

        fClear_Default = fClear_Both
    };
    typedef int TClearType;

    void ClearObjects(TClearType type = fClear_Default);

private:
    // Prohibit copy constructor and assignment operator
    CPluginMessage(const CPluginMessage& value);
    CPluginMessage& operator=(const CPluginMessage& value);

    // data
    TId               m_Id;

    IReporter* m_Reporter;
};


/////////////////// CPluginMessage inline methods

inline
CPluginMessage::TId CPluginMessage::GetId(void) const
{
    return m_Id;
}



/////////////////// end of CPluginMessage inline methods


END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE

#endif // GUI_PLUGIN_PLUGINMESSAGE_HPP
/* Original file checksum: lines: 93, chars: 2469, CRC32: abd79101 */