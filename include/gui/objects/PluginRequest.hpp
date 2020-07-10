/* $Id: PluginRequest.hpp 14666 2007-07-09 13:40:22Z dicuccio $
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

#ifndef GUI_CORE_PLUGIN_PLUGINREQUEST_HPP
#define GUI_CORE_PLUGIN_PLUGINREQUEST_HPP


// generated includes
#include <gui/objects/PluginRequest_.hpp>
#include <gui/objects/PluginCommand.hpp>

// generated classes

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::



class NCBI_GUIOBJECTS_EXPORT CPluginRequest : public CPluginRequest_Base
{
    typedef CPluginRequest_Base Tparent;
public:
    // constructor
    CPluginRequest(void);
    // destructor
    ~CPluginRequest(void);

    // a plugin request is a variant selecting between three command types
    // this utility returns the command objec, whichever one is set
    const CPluginCommand& GetCommand(void) const;
    CPluginCommand&       SetCommand(void);

    // utility functions to ease the syntax of creating new commands
    CPluginCommand& SetCommand(CPluginCommand::TCommand cmd);

private:
    // Prohibit copy constructor and assignment operator
    CPluginRequest(const CPluginRequest& value);
    CPluginRequest& operator=(const CPluginRequest& value);

};



/////////////////// CPluginRequest inline methods

// constructor
inline
CPluginRequest::CPluginRequest(void)
{
}


/////////////////// end of CPluginRequest inline methods


END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE

#endif // GUI_CORE_PLUGIN_PLUGINREQUEST_HPP
/* Original file checksum: lines: 93, chars: 2467, CRC32: 3ad7a1c6 */