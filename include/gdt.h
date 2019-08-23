#ifndef __GENOS__GDT_H
#define __GENOS__GDT_H

#include <common/types.h>

namespace genos
{
    
    class GlobalDescriptorTable
    {
        public:

            class SegmentDescriptor
            {
                private:
                    genos::common::uint16_t limit_lo;
                    genos::common::uint16_t base_lo;
                    genos::common::uint8_t base_hi;
                    genos::common::uint8_t type;
                    genos::common::uint8_t limit_hi;
                    genos::common::uint8_t base_vhi;

                public:
                    SegmentDescriptor(genos::common::uint32_t base, genos::common::uint32_t limit, genos::common::uint8_t type);
                    genos::common::uint32_t Base();
                    genos::common::uint32_t Limit();
            } __attribute__((packed));

        private:
            SegmentDescriptor nullSegmentSelector;
            SegmentDescriptor unusedSegmentSelector;
            SegmentDescriptor codeSegmentSelector;
            SegmentDescriptor dataSegmentSelector;

        public:

            GlobalDescriptorTable();
            ~GlobalDescriptorTable();

            genos::common::uint16_t CodeSegmentSelector();
            genos::common::uint16_t DataSegmentSelector();
    };

}

#endif
