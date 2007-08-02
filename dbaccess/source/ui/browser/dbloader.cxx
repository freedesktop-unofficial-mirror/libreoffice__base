/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: dbloader.cxx,v $
 *
 *  $Revision: 1.30 $
 *
 *  last change: $Author: hr $ $Date: 2007-08-02 14:26:15 $
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

//#ifndef _SFXFRAME_HXX
//#include <sfx2/frame.hxx>
//#endif
#ifndef _TOOLKIT_HELPER_VCLUNOHELPER_HXX_
#include <toolkit/helper/vclunohelper.hxx>
#endif
#ifndef _URLOBJ_HXX //autogen
#include <tools/urlobj.hxx>
#endif
#ifndef _TOOLKIT_AWT_VCLXWINDOW_HXX_
#include <toolkit/awt/vclxwindow.hxx>
#endif
#ifndef _COM_SUN_STAR_FRAME_XCONTROLLER_HPP_
#include <com/sun/star/frame/XController.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XFRAME_HPP_
#include <com/sun/star/frame/XFrame.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XFRAMELOADER_HPP_
#include <com/sun/star/frame/XFrameLoader.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XLOADEVENTLISTENER_HPP_
#include <com/sun/star/frame/XLoadEventListener.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XSINGLESERVICEFACTORY_HPP_
#include <com/sun/star/lang/XSingleServiceFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XSET_HPP_
#include <com/sun/star/container/XSet.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_REGISTRY_XREGISTRYKEY_HPP_
#include <com/sun/star/registry/XRegistryKey.hpp>
#endif
#ifndef _CPPUHELPER_IMPLBASE2_HXX_
#include <cppuhelper/implbase2.hxx>
#endif
#ifndef _COMPHELPER_SEQUENCEASHASHMAP_HXX_
#include <comphelper/sequenceashashmap.hxx>
#endif
#ifndef _DBU_REGHELPER_HXX_
#include "dbu_reghelper.hxx"
#endif
#ifndef _COM_SUN_STAR_LANG_XINITIALIZATION_HPP_
#include <com/sun/star/lang/XInitialization.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XCHILD_HPP_
#include <com/sun/star/container/XChild.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XDATASOURCE_HPP_
#include <com/sun/star/sdbc/XDataSource.hpp>
#endif
#ifndef DBACCESS_SHARED_DBUSTRINGS_HRC
#include "dbustrings.hrc"
#endif
#ifndef _SV_SVAPP_HXX 
#include <vcl/svapp.hxx>
#endif
#ifndef DBAUI_TOOLS_HXX
#include "UITools.hxx"
#endif


using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::registry;
using ::com::sun::star::sdbc::XDataSource;
using namespace dbaui;

class DBContentLoader : public ::cppu::WeakImplHelper2< XFrameLoader, XServiceInfo>
{
private:
    ::rtl::OUString						m_aURL;
    Sequence< PropertyValue>			m_aArgs;
    Reference< XLoadEventListener > 	m_xListener;
    Reference< XFrame > 				m_xFrame;
    Reference< XMultiServiceFactory >	m_xServiceFactory;
public:
    DBContentLoader(const Reference< XMultiServiceFactory >&);
    ~DBContentLoader();

    // XServiceInfo
    ::rtl::OUString					SAL_CALL getImplementationName() throw(  );
    sal_Bool 						SAL_CALL supportsService(const ::rtl::OUString& ServiceName) throw(  );
    Sequence< ::rtl::OUString > 	SAL_CALL getSupportedServiceNames(void) throw(  );
    
    // static methods
    static ::rtl::OUString 			getImplementationName_Static() throw(  )
    {
        return ::rtl::OUString::createFromAscii("org.openoffice.comp.dbu.DBContentLoader");
    }
    static Sequence< ::rtl::OUString> getSupportedServiceNames_Static(void) throw(  );
    static ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >
            SAL_CALL Create(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >&);

    // XLoader
    virtual void SAL_CALL load(	const Reference< XFrame > & _rFrame, const ::rtl::OUString& _rURL,
                                const Sequence< PropertyValue >& _rArgs,
                                const Reference< XLoadEventListener > & _rListener) throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL cancel(void) throw();
};
DBG_NAME(DBContentLoader)

DBContentLoader::DBContentLoader(const Reference< XMultiServiceFactory >& _rxFactory)
    :m_xServiceFactory(_rxFactory)
{
    DBG_CTOR(DBContentLoader,NULL);

}
// -------------------------------------------------------------------------

DBContentLoader::~DBContentLoader()
{

    DBG_DTOR(DBContentLoader,NULL);
}
// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
extern "C" void SAL_CALL createRegistryInfo_DBContentLoader()
{
    static ::dbaui::OMultiInstanceAutoRegistration< DBContentLoader > aAutoRegistration;
}
// -------------------------------------------------------------------------
Reference< XInterface > SAL_CALL DBContentLoader::Create( const Reference< XMultiServiceFactory >  & rSMgr )
{
    return *(new DBContentLoader(rSMgr));
}
// -------------------------------------------------------------------------
// XServiceInfo
::rtl::OUString SAL_CALL DBContentLoader::getImplementationName() throw(  )
{
    return getImplementationName_Static();
}
// -------------------------------------------------------------------------

// XServiceInfo
sal_Bool SAL_CALL DBContentLoader::supportsService(const ::rtl::OUString& ServiceName) throw(  )
{
    Sequence< ::rtl::OUString > aSNL = getSupportedServiceNames();
    const ::rtl::OUString * pBegin	= aSNL.getConstArray();
    const ::rtl::OUString * pEnd	= pBegin + aSNL.getLength();
    for( ; pBegin != pEnd; ++pBegin)
        if( *pBegin == ServiceName )
            return sal_True;
    return sal_False;
}
// -------------------------------------------------------------------------
// XServiceInfo
Sequence< ::rtl::OUString > SAL_CALL DBContentLoader::getSupportedServiceNames(void) throw(  )
{
    return getSupportedServiceNames_Static();
}
// -------------------------------------------------------------------------
// ORegistryServiceManager_Static
Sequence< ::rtl::OUString > DBContentLoader::getSupportedServiceNames_Static(void) throw(  )
{
    Sequence< ::rtl::OUString > aSNS( 2 );
    aSNS.getArray()[0] = ::rtl::OUString::createFromAscii("com.sun.star.frame.FrameLoader");
    aSNS.getArray()[1] = ::rtl::OUString::createFromAscii("com.sun.star.sdb.ContentLoader");
    return aSNS;
}
// -------------------------------------------------------------------------
extern "C" void SAL_CALL writeDBLoaderInfo(void* pRegistryKey)
{
    Reference< XRegistryKey> xKey(reinterpret_cast< XRegistryKey*>(pRegistryKey)); 

    // register content loader for dispatch
    ::rtl::OUString aImpl = ::rtl::OUString::createFromAscii("/");
    aImpl += DBContentLoader::getImplementationName_Static();

    ::rtl::OUString aImpltwo = aImpl;
    aImpltwo += ::rtl::OUString::createFromAscii("/UNO/Loader");
    Reference< XRegistryKey> xNewKey = xKey->createKey( aImpltwo );
    aImpltwo = aImpl;
    aImpltwo += ::rtl::OUString::createFromAscii("/Loader");
    Reference< XRegistryKey >  xLoaderKey = xKey->createKey( aImpltwo );
    xNewKey = xLoaderKey->createKey( ::rtl::OUString::createFromAscii("Pattern") );
    xNewKey->setAsciiValue( ::rtl::OUString::createFromAscii(".component:DB*") );
}

// -----------------------------------------------------------------------
void SAL_CALL DBContentLoader::load(const Reference< XFrame > & rFrame, const ::rtl::OUString& rURL,
        const Sequence< PropertyValue >& rArgs,
        const Reference< XLoadEventListener > & rListener) throw(::com::sun::star::uno::RuntimeException)
{
    m_xFrame	= rFrame;
    m_xListener = rListener;
    m_aURL		= rURL;
    m_aArgs		= rArgs;

    INetURLObject aParser(rURL);
    // ich benutze nicht maURL, sondern rURL, denn zwischen dem Constructor und diesem Load hier kann sich die ::com::sun::star::util::URL des Objektes
    // schon geaendert haben (zum Beispiel durch Umbenennen)
    Reference< XController >	xController;
    sal_Bool bAttachModel = sal_False;
    if(aParser.GetMainURL(INetURLObject::DECODE_TO_IURI) == URL_COMPONENT_FORMGRIDVIEW)
        xController.set(m_xServiceFactory->createInstance(::rtl::OUString::createFromAscii("org.openoffice.comp.dbu.OFormGridView")),UNO_QUERY);
    else if(aParser.GetMainURL(INetURLObject::DECODE_TO_IURI) == URL_COMPONENT_DATASOURCEBROWSER )// construct the control
        xController.set(m_xServiceFactory->createInstance(::rtl::OUString::createFromAscii("org.openoffice.comp.dbu.ODatasourceBrowser")),UNO_QUERY);
    else if ( (bAttachModel = (aParser.GetMainURL(INetURLObject::DECODE_TO_IURI) == URL_COMPONENT_QUERYDESIGN)) )// construct the control
        xController.set(m_xServiceFactory->createInstance(::rtl::OUString::createFromAscii("org.openoffice.comp.dbu.OQueryDesign")),UNO_QUERY);
    else if ( (bAttachModel = (aParser.GetMainURL(INetURLObject::DECODE_TO_IURI) == URL_COMPONENT_TABLEDESIGN)) ) // construct the control
        xController.set(m_xServiceFactory->createInstance(::rtl::OUString::createFromAscii("org.openoffice.comp.dbu.OTableDesign")),UNO_QUERY);
    else if ( (bAttachModel = (aParser.GetMainURL(INetURLObject::DECODE_TO_IURI) == URL_COMPONENT_RELATIONDESIGN)) )// construct the control
        xController.set(m_xServiceFactory->createInstance(::rtl::OUString::createFromAscii("org.openoffice.comp.dbu.ORelationDesign")),UNO_QUERY);
    else if ( aParser.GetMainURL(INetURLObject::DECODE_TO_IURI) == URL_COMPONENT_REPORTDESIGN )// construct the control
    {
        ::comphelper::SequenceAsHashMap lDescriptor(rArgs);
        sal_Bool bPreview = lDescriptor.getUnpackedValueOrDefault(INFO_PREVIEW, sal_False );
        if ( bPreview )
        {
            if (rListener.is())
                rListener->loadCancelled(this);
            return;
        }
        Reference< XModel > xModel   = lDescriptor.getUnpackedValueOrDefault(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Model")), Reference< XModel >());
        if ( xModel.is() )
        {
            xController.set(m_xServiceFactory->createInstance(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.sdb.ReportDesign"))),UNO_QUERY);			
            if ( xController.is() )
            {
                xController->attachModel(xModel);
                xModel->connectController( xController );
                xModel->setCurrentController(xController);
            }
        }
    }
    else
        OSL_ENSURE(0,"wrong dispatch url!");
    
    sal_Bool bSuccess = xController.is();
    if(bSuccess)
    {
        Reference<XModel> xModel;
        if ( bAttachModel )
        {			
            PropertyValue aValue;
            const PropertyValue* pIter	= m_aArgs.getConstArray();
            const PropertyValue* pEnd		= pIter + m_aArgs.getLength();

            for ( ; ( pIter != pEnd ) && !xModel.is(); ++pIter )
            {
                if(0 == pIter->Name.compareToAscii(PROPERTY_DATASOURCE))
                {
                    Reference<XDataSource> xProp(pIter->Value,UNO_QUERY);
                    xModel.set(getDataSourceOrModel(xProp),UNO_QUERY);
                    break;
                }
                else if(0 == pIter->Name.compareToAscii(PROPERTY_DATASOURCENAME))
                {
                    ::rtl::OUString sDataSource;
                    pIter->Value >>= sDataSource;
                    
                    Reference< XNameAccess > xDatabaseContext(m_xServiceFactory->createInstance(SERVICE_SDB_DATABASECONTEXT), UNO_QUERY);
                    xModel.set(getDataSourceOrModel(getDataSourceByName_displayError(xDatabaseContext,sDataSource,NULL,m_xServiceFactory,sal_False)),UNO_QUERY);
                    break;
                }
                else if ( 0 == pIter->Name.compareToAscii( PROPERTY_ACTIVECONNECTION ) )
                {
                    Reference< XChild > xAsChild( pIter->Value, UNO_QUERY );
                    if ( xAsChild.is() )
                    {
                        OSL_ENSURE( Reference< XDataSource >( xAsChild->getParent(), UNO_QUERY ).is(),
                            "DBContentLoader::load: a connection whose parent is no data source?" );
                        xModel.set(getDataSourceOrModel( xAsChild->getParent() ),UNO_QUERY);
                    }
                }
            }
            if ( (bSuccess = ( xModel.is() && xModel->getURL().getLength() != 0)) )
            {
                try
                {
                    xController->attachModel(xModel);
                    //xModel->setCurrentController(xController);
                }
                catch( const Exception& )
                {
                    OSL_ENSURE( sal_False, "DBContentLoader::load: caught an exception!" );
                    bSuccess = sal_False;
                }
            }

            OSL_ENSURE( bSuccess, "DBContentLoader::load: missing the required arguments - could not initialize the query design!" );
        }
        // init controller
        if ( bSuccess )
        {
            ::vos::OGuard aGuard(Application::GetSolarMutex());
            // and initialize
            try
            {
                Reference<XInitialization > xIni(xController,UNO_QUERY);
                PropertyValue aFrame(::rtl::OUString::createFromAscii("Frame"),0,makeAny(rFrame),PropertyState_DIRECT_VALUE);
                Sequence< Any > aArgs(m_aArgs.getLength()+1);

                Any* pBegin = aArgs.getArray();
                Any* pEnd	= pBegin + aArgs.getLength();
                *pBegin <<= aFrame;
                const PropertyValue* pIter		= m_aArgs.getConstArray();
                for(++pBegin;pBegin != pEnd;++pBegin,++pIter)
                {
                    *pBegin <<= *pIter;
                }
                
                xIni->initialize(aArgs);
            }
            catch(Exception&)
            {
                bSuccess = sal_False;
                try
                {
                    if ( xController.is() )
                        xController->attachModel( NULL );
                }
                catch( const Exception& )
                {
                    OSL_ENSURE( sal_False, "DBContentLoader::load: caught an exception!" );
                }
            }
        }

    }

    // assign controller and frame
    if (bSuccess && rListener.is())
    {
        if ( xController.is() && rFrame.is() )
            xController->attachFrame(rFrame);
        rListener->loadFinished(this);
    }
    else if (!bSuccess && rListener.is())
        rListener->loadCancelled(this);
}

// -----------------------------------------------------------------------
void DBContentLoader::cancel(void) throw()
{
}
