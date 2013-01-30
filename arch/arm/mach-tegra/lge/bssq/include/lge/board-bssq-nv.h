/*
 * The header file for X2 NV
 *
 * Copyright (C) 2011 LGE, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 */

#ifndef __MACH_TEGRA_X2_NV_H
#define __MACH_TEGRA_X2_NV_H

//                                                                            
#define LGE_NVDATA_PARTITION			"/dev/block/mmcblk0p6"

// modify this file and /android/vendor/lge/bssq/tegra/core/system/fastboot/nva_utils.h
typedef enum{
	LGE_NVDATA_NVA_STR_OFFSET 		= 0x1000,  // 32byte string
	LGE_NVDATA_WEB_DN_STR_OFFSET 		= 0x1020,  // 32byte string 
	LGE_NVDATA_MUIC_PATH_STR_OFFSET 	= 0x1040,  // 32byte string 
	LGE_NVDATA_SMPL_CNT_STR_OFFSET 		= 0x1060,  // 32byte string 
	LGE_NVDATA_ROM_STR_OFFSET 		= 0x1080,  // 32byte string 
	LGE_NVDATA_WARM_BOOT_FLAG_OFFSET 	= 0x10a0,  // 32byte string 
	LGE_NVDATA_FOTA_PT_FLAG_OFFSET 		= 0x10c0,  // 32byte string 
	LGE_NVDATA_IMEI_STR_OFFSET 		= 0x10e0,  // 32byte string 
        #if defined(CONFIG_KS1001) || defined(CONFIG_KS1103)
	LGE_NVDATA_BOARD_DN_STR_OFFSET 		= 0x1100,  // 32byte string 
	LGE_NVDATA_DEVPIN_PASS_STR_OFFSET 	= 0x1120,  // 32byte string 
	LGE_NVDATA_DEVPIN_CHECK_STR_OFFSET 	= 0x1140,  // 32byte string 
        #endif
}lge_nvdata_offset;

extern int lge_nvdata_read(lge_nvdata_offset offset, char* buf, int size);
extern int lge_nvdata_write(lge_nvdata_offset offset, char* buf, int size);

/*
                                                                            

                                                                                                    
             
                                    

                                                           
                                                          
                                                            
                                                           

                                                                                               
                                                                   
                                                                                    

                                      
                                                             
                                       

                                                       
                                                                                   
                                                     

                                      
                                     
        

                                  
                                                                                   

                                                           

                                                                        
                                                                              
                                                                                

                                                             

                                                      
                                                         

                                                             
                                                              

                                                            
                                                                           
                                                      
                                                                          
                                                                              
                                                                            
                                                   
                   

                           
                                                  
                                                 
                                                 
                                                 

                       
                                                       
                                                       
                     

                                               
                                              
                                               


                  
                                                
                                               
                                                                                                    
*/
#endif /* __MACH_TEGRA_X2_NV_H */
