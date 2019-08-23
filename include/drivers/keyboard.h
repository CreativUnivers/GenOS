
#ifndef __GENOS__DRIVERS__KEYBOARD_H
#define __GENOS__DRIVERS__KEYBOARD_H

#include <common/types.h>
#include <hrdwcom/interrupts.h>
#include <drivers/driver.h>
#include <hrdwcom/port.h>

namespace genos
{
    namespace drivers
    {
    
        class KeyboardEventHandler
        {
        public:
            KeyboardEventHandler();

            virtual void OnKeyDown(char);
            virtual void OnKeyUp(char);
        };
        
        class KeyboardDriver : public genos::hrdwcom::InterruptHandler, public Driver
        {
            genos::hrdwcom::Port8Bit dataport;
            genos::hrdwcom::Port8Bit commandport;
            
            KeyboardEventHandler* handler;
        public:
            KeyboardDriver(genos::hrdwcom::InterruptManager* manager, KeyboardEventHandler *handler);
            ~KeyboardDriver();
            virtual genos::common::uint32_t HandleInterrupt(genos::common::uint32_t esp);
            virtual void Activate();
        };

    }
}
    
#endif