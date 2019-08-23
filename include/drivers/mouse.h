
#ifndef __GENOS__DRIVERS__MOUSE_H
#define __GENOS__DRIVERS__MOUSE_H

#include <common/types.h>
#include <hrdwcom/port.h>
#include <drivers/driver.h>
#include <hrdwcom/interrupts.h>

namespace genos
{
    namespace drivers
    {
    
        class MouseEventHandler
        {
        public:
            MouseEventHandler();

            virtual void OnActivate();
            virtual void OnMouseDown(genos::common::uint8_t button);
            virtual void OnMouseUp(genos::common::uint8_t button);
            virtual void OnMouseMove(int x, int y);
        };
        
        
        class MouseDriver : public genos::hrdwcom::InterruptHandler, public Driver
        {
            genos::hrdwcom::Port8Bit dataport;
            genos::hrdwcom::Port8Bit commandport;
            genos::common::uint8_t buffer[3];
            genos::common::uint8_t offset;
            genos::common::uint8_t buttons;

            MouseEventHandler* handler;
        public:
            MouseDriver(genos::hrdwcom::InterruptManager* manager, MouseEventHandler* handler);
            ~MouseDriver();
            virtual genos::common::uint32_t HandleInterrupt(genos::common::uint32_t esp);
            virtual void Activate();
        };

    }
}
    
#endif
