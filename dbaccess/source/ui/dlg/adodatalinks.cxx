/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: adodatalinks.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: vg $ $Date: 2007-05-25 10:48:32 $
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


#if defined(WIN) || defined(WNT)
#if defined _MSC_VER
#pragma warning(push, 1)
#pragma warning(disable: 4917)
#endif
#include "msdasc.h"        // OLE DB Service Component header
#if defined _MSC_VER
#pragma warning(push, 1)
#endif
#include "stdio.h"

#include <initguid.h>  // Include only once in your application
#include <adoid.h>     // needed for CLSID_CADOConnection
#include <adoint.h>    // needed for ADOConnection

#ifndef _DBAUI_ADO_DATALINK_HXX_
#include "adodatalinks.hxx"
#endif

BSTR PromptEdit(long hWnd,BSTR connstr);
BSTR PromptNew(long hWnd);

::rtl::OUString getAdoDatalink(long hWnd,::rtl::OUString& oldLink)
{
    ::rtl::OUString dataLink;
    if (oldLink.getLength())
    {
        dataLink=reinterpret_cast<sal_Unicode *>(PromptEdit(hWnd,(BSTR)oldLink.getStr()));
    }
    else
        dataLink=reinterpret_cast<sal_Unicode *>(PromptNew(hWnd));
    return dataLink;
}
BSTR PromptNew(long hWnd)
{
    BSTR connstr=NULL;
    HRESULT hr;
    IDataSourceLocator* dlPrompt = NULL;
    ADOConnection* piTmpConnection = NULL;
    BSTR _result=NULL;

     // Initialize COM
     ::CoInitialize( NULL );
     
    // Instantiate DataLinks object.
      hr = CoCreateInstance(
                    CLSID_DataLinks,				//clsid -- Data Links UI
                    NULL,							//pUnkOuter
                    CLSCTX_INPROC_SERVER,			//dwClsContext
                    IID_IDataSourceLocator,		//riid
                    (void**)&dlPrompt	//ppvObj
                    );
    if( FAILED( hr ) )
    {
        piTmpConnection->Release( );
        dlPrompt->Release( );
        return connstr;
    }
    
    dlPrompt->put_hWnd(hWnd);
    if( FAILED( hr ) )
    {
        piTmpConnection->Release( );
        dlPrompt->Release( );
        return connstr;
    }

    // Prompt for connection information.
    hr = dlPrompt->PromptNew((IDispatch **)&piTmpConnection);

    if( FAILED( hr ) || !piTmpConnection ) 
    {
        dlPrompt->Release( );
        return connstr;
    }

    hr = piTmpConnection->get_ConnectionString(&_result);
    if( FAILED( hr ) )
    {
        piTmpConnection->Release( );
        dlPrompt->Release( );
        return connstr;
    }

    piTmpConnection->Release( );
    dlPrompt->Release( );
    CoUninitialize();
    return _result;
}

BSTR PromptEdit(long hWnd,BSTR connstr)
{
    HRESULT hr;
    IDataSourceLocator* dlPrompt = NULL;
    ADOConnection* piTmpConnection = NULL;
    BSTR _result=NULL;

     // Initialize COM
     ::CoInitialize( NULL );

     hr = CoCreateInstance(CLSID_CADOConnection, 
                NULL,
                CLSCTX_INPROC_SERVER,
                IID_IADOConnection,
                (LPVOID *)&piTmpConnection);
    if( FAILED( hr ) )
    {
        piTmpConnection->Release( );
        return connstr;
    }

     
    hr = piTmpConnection->put_ConnectionString(connstr);
    if( FAILED( hr ) )
    {
        piTmpConnection->Release( );
        return connstr;
    }
    
    // Instantiate DataLinks object.
      hr = CoCreateInstance(
                    CLSID_DataLinks,				//clsid -- Data Links UI
                    NULL,							//pUnkOuter
                    CLSCTX_INPROC_SERVER,			//dwClsContext
                    IID_IDataSourceLocator,		//riid
                    (void**)&dlPrompt	//ppvObj
                    );
    if( FAILED( hr ) )
    {
        piTmpConnection->Release( );
        dlPrompt->Release( );
        return connstr;
    }
    
    dlPrompt->put_hWnd(hWnd);
    if( FAILED( hr ) )
    {
        piTmpConnection->Release( );
        dlPrompt->Release( );
        return connstr;
    }

    VARIANT_BOOL pbSuccess;
        
    // Prompt for connection information.
    hr = dlPrompt->PromptEdit((IDispatch **)&piTmpConnection,&pbSuccess);
    if( SUCCEEDED( hr ) && FALSE == pbSuccess ) //if user press cancel then FALSE == pbSuccess
    {
        piTmpConnection->Release( );
        dlPrompt->Release( );
        return connstr;
    }

    if( FAILED( hr ) ) 
    {
        // Prompt for new connection information.
        piTmpConnection->Release( );
        piTmpConnection = NULL;
        hr = dlPrompt->PromptNew((IDispatch **)&piTmpConnection);
        if(  FAILED( hr ) || !piTmpConnection )
        {
            dlPrompt->Release( );
            return connstr;
        }
    }

    hr = piTmpConnection->get_ConnectionString(&_result);
    if( FAILED( hr ) )
    {
        piTmpConnection->Release( );
        dlPrompt->Release( );
        return connstr;
    }

    piTmpConnection->Release( );
    dlPrompt->Release( );
    CoUninitialize();
    return _result;
}
#endif
