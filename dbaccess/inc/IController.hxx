/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: IController.hxx,v $
 * $Revision: 1.5 $
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#ifndef DBAUI_ICONTROLLER_HXX
#define DBAUI_ICONTROLLER_HXX

#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
#include <com/sun/star/uno/Sequence.hxx>
#endif
#ifndef DBAUI_IREFERENCE_HXX
#include "IReference.hxx"
#endif
#include "dbaccessdllapi.h"

namespace com { namespace sun { namespace star {
    namespace util {
        struct URL;
    }
    namespace frame {
        class XController;
    }
} } }

namespace dbaui
{
    // interface for controller depended calls like commands
    class DBACCESS_DLLPUBLIC IController : public IReference
    {
    public:
        /** executes the given command without checking if it is allowed
            @param	_rCommand	the URL of the command
        */
        virtual void executeUnChecked(const ::com::sun::star::util::URL& _rCommand, const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& aArgs) = 0;

        /** executes the given command only when it is allowed
            @param	_rCommand	
                the URL of the command
        */
        virtual void executeChecked(const ::com::sun::star::util::URL& _rCommand, const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& aArgs) = 0;

        /** executes the given command without checking if it is allowed
            @param	_nCommandId
                the id of the command URL 
        */
        virtual void executeUnChecked(sal_uInt16 _nCommandId, const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& aArgs) = 0;

        /** executes the given command only when it is allowed
            @param	_nCommandId
                the id of the command URL 
        */
        virtual void executeChecked(sal_uInt16 _nCommandId, const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& aArgs) = 0;


        /** checks if the given Command is enabled
            @param	_nCommandId
                the id of the command URL 
            
            @return	
                <TRUE/> if the command is allowed, otherwise <FALSE/>.
        */
        virtual sal_Bool isCommandEnabled(sal_uInt16 _nCommandId) const = 0;

        /** checks if the given Command is enabled
            @param	_rCompleteCommandURL
                the URL of the command
            
            @return	
                <TRUE/> if the command is allowed, otherwise <FALSE/>.
        */
        virtual sal_Bool isCommandEnabled( const ::rtl::OUString& _rCompleteCommandURL ) const = 0;

        /** notifyHiContrastChanged will be called when the hicontrast mode changed.
            @param	_bHiContrast
                <TRUE/> when in hicontrast mode.
        */
        virtual void notifyHiContrastChanged() {}

        /** checks if the selected data source is read only
            @return 
                <TRUE/> if read only, otherwise <FALSE/>
        */
        virtual sal_Bool isDataSourceReadOnly() const = 0;

        /** provides access to the model of the controller

            This must be the same model as returned by XController::getModel, and might be <NULL/> when
            the controller does not have an own model.
        */
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::frame::XController > SAL_CALL
                getXController(void) throw( ::com::sun::star::uno::RuntimeException ) = 0;
    };
}
#endif // DBAUI_ICONTROLLER_HXX
