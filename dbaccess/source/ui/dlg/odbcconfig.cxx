/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: odbcconfig.cxx,v $
 *
 *  $Revision: 1.19 $
 *
 *  last change: $Author: rt $ $Date: 2007-07-24 12:08:47 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_dbaccess.hxx"

#ifndef _DBAUI_ODBC_CONFIG_HXX_
#include "odbcconfig.hxx"
#endif
#ifndef _RTL_USTRING_HXX_
#include <rtl/ustring.hxx>
#endif
#ifndef _RTL_USTRBUF_HXX_
#include <rtl/ustrbuf.hxx>
#endif
#ifndef _OSL_DIAGNOSE_H_
#include <osl/diagnose.h>
#endif
#ifndef _OSL_PROCESS_H_
#include <osl/process.h>
#endif
#ifndef _THREAD_HXX_
#include <osl/thread.hxx>
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif

#ifdef HAVE_ODBC_SUPPORT

#ifdef WIN
#define ODBC_LIBRARY	"ODBC.DLL"
#define ODBC_UI_LIBRARY	"ODBCINST.DLL"
#endif
#if defined WNT
#define ODBC_LIBRARY	"ODBC32.DLL"
#define ODBC_UI_LIBRARY	"ODBCCP32.DLL"
#endif
#ifdef UNX
#ifdef MACOSX
#define ODBC_LIBRARY		"libiodbc.dylib"
#define ODBC_UI_LIBRARY		"libiodbcinst.dylib"
#else
#define ODBC_LIBRARY_1		"libodbc.so.1"
#define ODBC_UI_LIBRARY_1	"libodbcinst.so.1"
#define ODBC_LIBRARY		"libodbc.so"
#define ODBC_UI_LIBRARY		"libodbcinst.so"
#endif
#endif

// just to go with calling convention of windows
// so don't touch this
#if defined(WIN) || defined(WNT)
#define SQL_API __stdcall
// At least under some circumstances, the below #include <odbc/sqlext.h> re-
// defines SQL_API to an empty string, leading to a compiler warning on MSC; to
// not break the current behavior, this is worked around by locally disabling
// that warning:
#if defined _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4005)
#endif
#endif // defined(WIN) || defined(WNT)

#ifdef SYSTEM_ODBC_HEADERS
#include <sqlext.h>
#else
#ifndef __SQLEXT_H
#include <odbc/sqlext.h>
#endif
#endif

#if defined(WIN) || defined(WNT)
#if defined _MSC_VER
#pragma warning(pop)
#endif
#undef SQL_API
#define SQL_API __stdcall
#endif // defined(WIN) || defined(WNT)
// from here on you can do what you want to


#else

#define ODBC_LIBRARY	""
#define ODBC_UI_LIBRARY	""

#endif	// HAVE_ODBC_SUPPORT

//.........................................................................
namespace dbaui
{
//.........................................................................


#ifdef HAVE_ODBC_SUPPORT
typedef SQLRETURN (SQL_API* TSQLManageDataSource) (SQLHWND hwndParent);
typedef SQLRETURN (SQL_API* TSQLAllocHandle) (SQLSMALLINT HandleType, SQLHANDLE InputHandle, SQLHANDLE*	OutputHandlePtr);
typedef SQLRETURN (SQL_API* TSQLFreeHandle) (SQLSMALLINT HandleType, SQLHANDLE Handle);
typedef SQLRETURN (SQL_API* TSQLSetEnvAttr) (SQLHENV EnvironmentHandle, SQLINTEGER Attribute, SQLPOINTER ValuePtr, SQLINTEGER StringLength);
typedef SQLRETURN (SQL_API* TSQLDataSources) (SQLHENV EnvironmentHandle, SQLUSMALLINT	Direction, SQLCHAR* ServerName,
                                SQLSMALLINT BufferLength1, SQLSMALLINT* NameLength1Ptr, SQLCHAR* Description, SQLSMALLINT BufferLength2, SQLSMALLINT* NameLength2Ptr);

#define NSQLManageDataSource(a) (*(TSQLManageDataSource)(m_pSQLManageDataSource))(a)
#define NSQLAllocHandle(a,b,c) (*(TSQLAllocHandle)(m_pAllocHandle))(a,b,c)
#define NSQLFreeHandle(a,b) (*(TSQLFreeHandle)(m_pFreeHandle))(a,b)
#define NSQLSetEnvAttr(a,b,c,d) (*(TSQLSetEnvAttr)(m_pSetEnvAttr))(a,b,c,d)
#define NSQLDataSources(a,b,c,d,e,f,g,h) (*(TSQLDataSources)(m_pDataSources))(a,b,c,d,e,f,g,h)
#endif

//=========================================================================
//= OOdbcLibWrapper
//=========================================================================
DBG_NAME(OOdbcLibWrapper)
//-------------------------------------------------------------------------
OOdbcLibWrapper::OOdbcLibWrapper()
    :m_pOdbcLib(NULL)
{
    DBG_CTOR(OOdbcLibWrapper,NULL);

}

//-------------------------------------------------------------------------
sal_Bool OOdbcLibWrapper::load(const sal_Char* _pLibPath)
{
    m_sLibPath = ::rtl::OUString::createFromAscii(_pLibPath);
#ifdef HAVE_ODBC_SUPPORT
    // load the module
    m_pOdbcLib = osl_loadModule(m_sLibPath.pData, SAL_LOADMODULE_NOW);
    return (NULL != m_pOdbcLib);
#endif
}

//-------------------------------------------------------------------------
void OOdbcLibWrapper::unload()
{
#ifdef HAVE_ODBC_SUPPORT
    if (isLoaded())
    {
        osl_unloadModule(m_pOdbcLib);
        m_pOdbcLib = NULL;
    }
#endif
}

//-------------------------------------------------------------------------
oslGenericFunction OOdbcLibWrapper::loadSymbol(const sal_Char* _pFunctionName)
{
    return osl_getFunctionSymbol(m_pOdbcLib, ::rtl::OUString::createFromAscii(_pFunctionName).pData);
}

//-------------------------------------------------------------------------
OOdbcLibWrapper::~OOdbcLibWrapper()
{
    unload();

    DBG_DTOR(OOdbcLibWrapper,NULL);
}

//=========================================================================
//= OOdbcEnumeration
//=========================================================================
struct OdbcTypesImpl
{
#ifdef HAVE_ODBC_SUPPORT
    SQLHANDLE	hEnvironment;
    OdbcTypesImpl() : hEnvironment(0) { }
#else
    void*		pDummy;
#endif
};
DBG_NAME(OOdbcEnumeration)
//-------------------------------------------------------------------------
OOdbcEnumeration::OOdbcEnumeration()
#ifdef HAVE_ODBC_SUPPORT
    :m_pAllocHandle(NULL)
    ,m_pSetEnvAttr(NULL)
    ,m_pDataSources(NULL)
    ,m_pImpl(new OdbcTypesImpl)
#endif
{
    DBG_CTOR(OOdbcEnumeration,NULL);

    sal_Bool bLoaded = load(ODBC_LIBRARY);
#ifdef ODBC_LIBRARY_1
    if ( !bLoaded )
        bLoaded = load(ODBC_LIBRARY_1);
#endif

    if ( bLoaded )
    {
#ifdef HAVE_ODBC_SUPPORT
        // load the generic functions
        m_pAllocHandle = loadSymbol("SQLAllocHandle");
        m_pFreeHandle = loadSymbol("SQLFreeHandle");
        m_pSetEnvAttr = loadSymbol("SQLSetEnvAttr");
        m_pDataSources = loadSymbol("SQLDataSources");

        // all or nothing
        if (!m_pAllocHandle || !m_pSetEnvAttr || !m_pDataSources || !m_pFreeHandle)
        {
            unload();
            m_pAllocHandle = m_pFreeHandle = m_pSetEnvAttr = m_pDataSources = NULL;
        }
#endif
    }
}

//-------------------------------------------------------------------------
OOdbcEnumeration::~OOdbcEnumeration()
{
    freeEnv();
    delete m_pImpl;

    DBG_DTOR(OOdbcEnumeration,NULL);
}

//-------------------------------------------------------------------------
sal_Bool OOdbcEnumeration::allocEnv()
{
    OSL_ENSURE(isLoaded(), "OOdbcEnumeration::allocEnv: not loaded!");
    if (!isLoaded())
        return sal_False;

#ifdef HAVE_ODBC_SUPPORT
    if (m_pImpl->hEnvironment)
        // nothing to do
        return sal_True;
    SQLRETURN nResult = NSQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_pImpl->hEnvironment);
    if (SQL_SUCCESS != nResult)
        // can't do anything without environment
        return sal_False;

    NSQLSetEnvAttr(m_pImpl->hEnvironment, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
    return sal_True;
#else
    return sal_False;
#endif
}

//-------------------------------------------------------------------------
void OOdbcEnumeration::freeEnv()
{
#ifdef HAVE_ODBC_SUPPORT
    if (m_pImpl->hEnvironment)
        NSQLFreeHandle(SQL_HANDLE_ENV, m_pImpl->hEnvironment);
    m_pImpl->hEnvironment  = 0;
#endif
}

//-------------------------------------------------------------------------
void OOdbcEnumeration::getDatasourceNames(StringBag& _rNames)
{
    OSL_ENSURE(isLoaded(), "OOdbcEnumeration::getDatasourceNames: not loaded!");
    if (!isLoaded())
        return;

    if (!allocEnv())
    {
        OSL_ENSURE(sal_False, "OOdbcEnumeration::getDatasourceNames: could not allocate an ODBC environment!");
        return;
    }

#ifdef HAVE_ODBC_SUPPORT
    // now that we have an environment collect the data source names
    UCHAR szDSN[SQL_MAX_DSN_LENGTH+1];
    SWORD pcbDSN;
    UCHAR szDescription[1024+1];
    SWORD pcbDescription;
    SQLRETURN nResult = SQL_SUCCESS;

    for (	nResult = NSQLDataSources(m_pImpl->hEnvironment, SQL_FETCH_FIRST, szDSN, sizeof(szDSN), &pcbDSN, szDescription, sizeof(szDescription), &pcbDescription);
            ;
            nResult = NSQLDataSources(m_pImpl->hEnvironment, SQL_FETCH_NEXT, szDSN, sizeof(szDSN), &pcbDSN, szDescription, sizeof(szDescription), &pcbDescription)
        )
    {
        if (nResult != SQL_SUCCESS)
            // no further error handling
            break;
        else
        {
            ::rtl::OUStringBuffer aCurrentDsn; aCurrentDsn.appendAscii(reinterpret_cast<const char*>(szDSN));
            _rNames.insert(aCurrentDsn.makeStringAndClear());
        }
    }
#endif
}

#ifdef HAVE_ODBC_ADMINISTRATION

//=========================================================================
//= ProcessTerminationWait
//=========================================================================
class ProcessTerminationWait : public ::osl::Thread
{
    oslProcess  m_hProcessHandle;
    Link        m_aFinishHdl;

public:
    ProcessTerminationWait( oslProcess _hProcessHandle, const Link& _rFinishHdl )
        :m_hProcessHandle( _hProcessHandle )
        ,m_aFinishHdl( _rFinishHdl )
    {
    }

protected:
    virtual void SAL_CALL run()
    {
        osl_joinProcess( m_hProcessHandle );
        Application::PostUserEvent( m_aFinishHdl );
    }
};

//=========================================================================
//= OOdbcManagement
//=========================================================================
//-------------------------------------------------------------------------
OOdbcManagement::OOdbcManagement( const Link& _rAsyncFinishCallback )
    :m_pProcessWait( NULL )
    ,m_aAsyncFinishCallback( _rAsyncFinishCallback )
{
}

//-------------------------------------------------------------------------
OOdbcManagement::~OOdbcManagement()
{
    // wait for our thread to be finished
    if ( m_pProcessWait.get() )
        m_pProcessWait->join();
}

//-------------------------------------------------------------------------
bool OOdbcManagement::manageDataSources_async()
{
    OSL_PRECOND( !isRunning(), "OOdbcManagement::manageDataSources_async: still running from the previous call!" );
    if ( isRunning() )
        return false;

    // this is done in an external process, due to #i78733#
    // (and note this whole functionality is supported on Windows only, ATM)
    ::rtl::OUString sExecutableName( RTL_CONSTASCII_USTRINGPARAM( "odbcconfig.exe" ) );
    oslProcess hProcessHandle(0);
    oslProcessError eError = osl_executeProcess( sExecutableName.pData, NULL, 0, 0, NULL, NULL, NULL, 0, &hProcessHandle );
    if ( eError != osl_Process_E_None )
        return false;

    m_pProcessWait.reset( new ProcessTerminationWait( hProcessHandle, m_aAsyncFinishCallback ) );
    m_pProcessWait->create();
    return true;
}

//-------------------------------------------------------------------------
bool OOdbcManagement::isRunning() const
{
    return ( m_pProcessWait.get() && m_pProcessWait->isRunning() );
}

#endif // HAVE_ODBC_ADMINISTRATION

//.........................................................................
}	// namespace dbaui
//.........................................................................
