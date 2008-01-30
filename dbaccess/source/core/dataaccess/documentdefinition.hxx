/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: documentdefinition.hxx,v $
 *
 *  $Revision: 1.26 $
 *
 *  last change: $Author: rt $ $Date: 2008-01-30 08:34:51 $
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

#ifndef _DBA_COREDATAACCESS_DOCUMENTDEFINITION_HXX_
#define _DBA_COREDATAACCESS_DOCUMENTDEFINITION_HXX_

#ifndef _CPPUHELPER_PROPSHLP_HXX
#include <cppuhelper/propshlp.hxx>
#endif
#ifndef _CPPUHELPER_IMPLBASE1_HXX_
#include <cppuhelper/implbase1.hxx>
#endif
#ifndef DBA_CONTENTHELPER_HXX
#include "ContentHelper.hxx"
#endif
#ifndef COMPHELPER_PROPERTYSTATECONTAINER_HXX
#include <comphelper/propertystatecontainer.hxx>
#endif
#ifndef _COMPHELPER_PROPERTY_ARRAY_HELPER_HXX_
#include <comphelper/proparrhlp.hxx>
#endif
#ifndef _DBASHARED_APITOOLS_HXX_
#include "apitools.hxx"
#endif
#ifndef _COMPHELPER_UNO3_HXX_
#include <comphelper/uno3.hxx>
#endif
#ifndef _COM_SUN_STAR_SDBC_XCONNECTION_HPP_
#include <com/sun/star/sdbc/XConnection.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XCOMPONENTLOADER_HPP_
#include <com/sun/star/frame/XComponentLoader.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XCONTROLLER_HPP_
#include <com/sun/star/frame/XController.hpp>
#endif
#ifndef _COM_SUN_STAR_EMBED_XSTATECHANGELISTENER_HPP_
#include <com/sun/star/embed/XStateChangeListener.hpp>
#endif

//........................................................................
namespace dbaccess
{
//........................................................................

    class OInterceptor;
    class OEmbeddedClientHelper;
//==========================================================================
//= ODocumentDefinition - a database "document" which is simply a link to a real
//=					  document
//==========================================================================

    typedef ::cppu::ImplHelper1<		::com::sun::star::embed::XComponentSupplier
                                >	ODocumentDefinition_Base;

class ODocumentDefinition
        :public OContentHelper
        ,public ::comphelper::OPropertyStateContainer
        ,public ::comphelper::OPropertyArrayUsageHelper< ODocumentDefinition >
        ,public ODocumentDefinition_Base
{
    ::com::sun::star::uno::Reference< ::com::sun::star::embed::XEmbeddedObject>			m_xEmbeddedObject;
    ::com::sun::star::uno::Reference< ::com::sun::star::embed::XStateChangeListener >	m_xListener;
    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XFramesSupplier >		m_xDesktop;
    ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection >             m_xLastKnownConnection;

    OInterceptor*																		m_pInterceptor;
    sal_Bool																			m_bForm; // <TRUE/> if it is a form
    sal_Bool																			m_bOpenInDesign;
    sal_Bool																			m_bInExecute;
    OEmbeddedClientHelper*																m_pClientHelper;

protected:
    virtual ~ODocumentDefinition();

public:

    ODocumentDefinition(
             const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >& _rxContainer
            ,const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >&
            ,const TContentPtr& _pImpl
            ,sal_Bool _bForm
            ,const ::com::sun::star::uno::Sequence< sal_Int8 >& _aClassID = ::com::sun::star::uno::Sequence< sal_Int8 >()
            ,const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection>& _xConnection = ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection>()
        );

// com::sun::star::lang::XTypeProvider
    DECLARE_TYPEPROVIDER( );

// ::com::sun::star::uno::XInterface
    DECLARE_XINTERFACE( )

// ::com::sun::star::lang::XServiceInfo
    DECLARE_SERVICE_INFO_STATIC();

// ::com::sun::star::beans::XPropertySet
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo > SAL_CALL getPropertySetInfo(  ) throw(::com::sun::star::uno::RuntimeException);

    // XComponentSupplier
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::util::XCloseable > SAL_CALL getComponent(  ) throw (::com::sun::star::uno::RuntimeException);

// OPropertySetHelper
    virtual ::cppu::IPropertyArrayHelper& SAL_CALL getInfoHelper();

    // XCommandProcessor
    virtual ::com::sun::star::uno::Any SAL_CALL execute( const ::com::sun::star::ucb::Command& aCommand, sal_Int32 CommandId, const ::com::sun::star::uno::Reference< ::com::sun::star::ucb::XCommandEnvironment >& Environment ) throw (::com::sun::star::uno::Exception, ::com::sun::star::ucb::CommandAbortedException, ::com::sun::star::uno::RuntimeException) ;

    // XRename
    virtual void SAL_CALL rename( const ::rtl::OUString& newName ) throw (::com::sun::star::sdbc::SQLException, ::com::sun::star::container::ElementExistException, ::com::sun::star::uno::RuntimeException);

    virtual ::com::sun::star::uno::Reference< ::com::sun::star::embed::XStorage> getStorage() const;

    sal_Bool save(sal_Bool _bApprove);
    sal_Bool saveAs();
    void closeObject();
    sal_Bool isModified();
    void fillReportData();
    inline sal_Bool isNewReport() const { return !m_bForm && !m_pImpl->m_aProps.bAsTemplate; }

    /** prepares closing the document component

        The method suspends the controller associated with the document, and saves the document
        if necessary.

        @return
            <TRUE/> if and only if the document component can be closed
    */
    bool prepareClose();

    static ::com::sun::star::uno::Sequence< sal_Int8 > getDefaultDocumentTypeClassId();

    /** does necessary initializations after our embedded object has been switched to ACTIVE
        @param _bOpenedInDesignMode
            determines whether the embedded object has been opened for designing it or for data display
    */
    void impl_onActivateEmbeddedObject();

    /** initializes a newly created view/controller which is displaying our embedded object

        Has only to be called if the respective embedded object has been loaded for design (and
        not for data entry)

        @param  _rxController
            the controller which belongs to the XModel of our (active) embedded object
    */
    void impl_initObjectEditView( const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XController >& _rxController );

    /** removes the given frame from the desktop's frame collection
        @raises ::com::sun::star::uno::RuntimeException
    */
    void impl_removeFrameFromDesktop_throw( const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XFrame >& _rxFrame );

    static ::rtl::OUString GetDocumentServiceFromMediaType( const ::com::sun::star::uno::Reference< ::com::sun::star::embed::XStorage >& xStorage
                                                    ,const ::rtl::OUString& sEntName 
                                                    ,const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _xORB
                                                    ,::com::sun::star::uno::Sequence< sal_Int8 >& _rClassId
                                                    );

protected:
    // OPropertyArrayUsageHelper
    virtual ::cppu::IPropertyArrayHelper* createArrayHelper( ) const;

    virtual void getPropertyDefaultByHandle( sal_Int32 _nHandle, ::com::sun::star::uno::Any& _rDefault ) const;
    // helper
    virtual void SAL_CALL disposing();

private:
    /** fills the load arguments
    */
    ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >
        fillLoadArgs(
            const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection>& _xConnection,
            const bool _bSuppressMacros,
            const bool _bReadOnly,
            const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& _rAdditionalArgs,
            ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& _out_rEmbeddedObjectDescriptor
        );

    /** loads the EmbeddedObject if not already loaded
        @param	_aClassID
            If set, it will be used to create the embedded object.
    */
    void loadEmbeddedObject(
                const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection>& _xConnection,
                const ::com::sun::star::uno::Sequence< sal_Int8 >& _aClassID,
                const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& _rAdditionalArgs,
                const bool _bSuppressMacros,
                const bool _bReadOnly
            );

    /** loads the embedded object, if not already loaded. No new object can be created with this method.
    */
    void    loadEmbeddedObject()
    {
        loadEmbeddedObject(
            NULL,
            ::com::sun::star::uno::Sequence< sal_Int8 >(),
            ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >(),
            false,
            false
        );
    }

    /** loads the embedded object for preview. Macros will be suppressed, and the document will
        be read-only.
    */
    void    loadEmbeddedObjectForPreview()
    {
        loadEmbeddedObject(
            NULL,
            ::com::sun::star::uno::Sequence< sal_Int8 >(),
            ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >(),
            true,
            true
        );
    }

    /** searches for read-only flag in the args of the model and sets it to the given value,
        if the value was not found, it will be appended.
        @param	_bReadOnly
            If <TRUE/> the document will be switched to readonly mode
    */
    void updateDocumentTitle();

    void registerProperties();

    //-------------------------------------------------------------------------
    //- commands
    //-------------------------------------------------------------------------

    void onCommandGetDocumentInfo( ::com::sun::star::uno::Any& _rInfo );
    void onCommandInsert( const ::rtl::OUString& _sURL, const ::com::sun::star::uno::Reference< ::com::sun::star::ucb::XCommandEnvironment >& Environment ) throw( ::com::sun::star::uno::Exception );
    void onCommandPreview( ::com::sun::star::uno::Any& _rImage );
    void onCommandOpenSomething( const ::com::sun::star::uno::Any& _rArgument, const bool _bActivate,
            const ::com::sun::star::uno::Reference< ::com::sun::star::ucb::XCommandEnvironment >& _rxEnvironment, ::com::sun::star::uno::Any& _out_rComponent );
};

//........................................................................
}	// namespace dbaccess
//........................................................................

#endif // _DBA_COREDATAACCESS_DOCUMENTDEFINITION_HXX_

