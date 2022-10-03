/*
   Copyright (c) 2020, The LineageOS Project

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <sys/system_properties.h>
#include <sys/_system_properties.h>

#include "property_service.h"
#include "vendor_init.h"

using android::base::GetProperty;

void property_override(char const prop[], char const value[]) {
  prop_info *pi;

  pi = (prop_info *)__system_property_find(prop);
  if (pi)
    __system_property_update(pi, value, strlen(value));
  else
    __system_property_add(prop, strlen(prop), value, strlen(value));
}

void vendor_load_properties() {
  int project_name = stoi(android::base::GetProperty("ro.boot.project_name", ""));
  int rf_version = stoi(android::base::GetProperty("ro.boot.rf_version", ""));
  switch(project_name){
    case 19805:
      /* OnePlus 8T */
      switch (rf_version){
        case 11:
          /* China */
          property_override("ro.product.model", "KB2000");
          break;
        case 13:
          /* India */
          property_override("ro.product.model", "KB2001");
          break;
        case 14:
          /* Europe */
          property_override("ro.product.model", "KB2003");
          break;
        case 15:
          /* Global / US Unlocked */
          property_override("ro.product.model", "KB2005");
          break;
        default:
          /* Generic */
          property_override("ro.product.model", "KB2005");
          break;
      }
      break;
    case 20809:
      /* OnePlus 8T T-Mobile */
      switch (rf_version){
        case 12:
          /* T-Mobile */
          property_override("ro.product.model", "KB2007");
          break;
        default:
          /* Generic */
          property_override("ro.product.model", "KB2005");
          break;
      }
      break;
    case 20828:
      /* OnePlus 9R */
      switch (rf_version){
      case 11:
          /* China */
          property_override("ro.product.model", "LE2100");
          break;
      case 13:
          /* India */
          property_override("ro.product.model", "LE2101");
          break;
      default:
          /* Generic */
          property_override("ro.product.model", "LE2101");
          break;
      }
      break;
  }
}
