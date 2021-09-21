//
//  detourHook.h
//  osxGlow
//
//  Created by TheArmKing on 21/09/21.
//

#ifndef detourHook_h
#define detourHook_h

#include <mach/mach.h>
#include <mach/mach_vm.h>
#include <mach/mach_init.h>

//detour hook
//very basic, no trampoline neeeded
#define size_of_jump (mach_msg_type_number_t)(sizeof(uintptr_t) * 2)
class detour {
    private:
        void* address;
        uint8_t opcodes_copy[size_of_jump];
        kern_return_t get_memory_protection(void* address, vm_prot_t &prot) {
            mach_vm_address_t addr = (mach_vm_address_t)address;
            mach_vm_size_t vmsize;
            vm_region_flavor_t flavor = VM_REGION_BASIC_INFO_64;
            vm_region_basic_info_data_64_t info;
            mach_msg_type_number_t infoCount = VM_REGION_BASIC_INFO_COUNT_64;
            mach_port_t object;
            kern_return_t err = mach_vm_region(mach_task_self(), &addr, &vmsize, flavor, (vm_region_info_64_t)&info, &infoCount, &object);
            
            if (err == KERN_SUCCESS)
                prot = info.protection;
            return err;
        }
    public:
        kern_return_t hook(void* func_addr, void* func) {
            address = func_addr;
            
            //thanks https://github.com/rodionovd/rd_route
            uint8_t opcodes[size_of_jump];
            
            opcodes[0] = 0xFF;
            opcodes[1] = 0x25;
            *((int*)&opcodes[2]) = 0;
            *((uintptr_t*)&opcodes[6]) = (uintptr_t)func;
            
            kern_return_t err = KERN_SUCCESS;
            
            vm_prot_t prot;
            err = get_memory_protection(address, prot);
            if (err != KERN_SUCCESS)
                return err;
            
            err = mach_vm_protect(mach_task_self(), (mach_vm_address_t)address, (mach_vm_size_t)size_of_jump, FALSE, VM_PROT_ALL);
            if (err != KERN_SUCCESS)
                return err;
            
            memcpy(&opcodes_copy, address, size_of_jump);
            
            memcpy(address, &opcodes, size_of_jump);
            
            err = mach_vm_protect(mach_task_self(), (mach_vm_address_t)address, (mach_vm_size_t)size_of_jump, FALSE, prot);
            
            return err;
        }
        kern_return_t unhook() {
            kern_return_t err = KERN_SUCCESS;
            
            vm_prot_t prot;
            err = get_memory_protection(address, prot);
            if (err != KERN_SUCCESS)
                return err;
            
            err = mach_vm_protect(mach_task_self(), (mach_vm_address_t)address, (mach_vm_size_t)size_of_jump, FALSE, VM_PROT_ALL);
            if (err != KERN_SUCCESS)
                return err;
            
            memcpy(address, &opcodes_copy, size_of_jump);
            
            err = mach_vm_protect(mach_task_self(), (mach_vm_address_t)address, (mach_vm_size_t)size_of_jump, FALSE, prot);
            
            return err;
        }
};
#undef size_of_jump

#endif /* detourHook_h */
