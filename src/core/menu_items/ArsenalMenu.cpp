#include "ArsenalMenu.h"
#include "core/display.h"
#include "core/utils.h"
#include "modules/arsenal/arsenal.h"
#include "modules/arsenal/arsenal_background.h"
#include "modules/arsenal/arsenal_config.h"
#include "modules/ir/ir_remote_app.h"

void ArsenalMenu::optionsMenu() {
    if (!arsenal_pin_check()) {
        displayRedStripe("Access denied");
        delay(1500);
        return;
    }

    options = {
        {"WiFi Arsenal",   [this]() { wifiArsenalMenu(); }  },
        {"BLE Arsenal",    [this]() { bleArsenalMenu(); }   },
        {"Intelligence",   [this]() { intelligenceMenu(); } },
        {"Evasion",        [this]() { evasionMenu(); }      },
        {"Phishing",       [this]() { phishingMenu(); }     },
        {"Sub-GHz / RF",   [this]() { rfMenu(); }           },
        {"Detection",      [this]() { detectionMenu(); }    },
        {"Comms",          [this]() { commsMenu(); }        },
        {"Utility",        [this]() { utilityMenu(); }      },
        {"Combos",         arsenal_combo_menu               },
        {"Scheduler",      arsenal_attack_scheduler         },
        {"Scripts",        arsenal_script_browser           },
        {"Session Log",    arsenal_session_log_menu         },
        {"Jam All",        arsenal_jam_all                  },
#if !LITE_VERSION
        {"Dashboard",      arsenal_remote_dashboard         },
#endif
        {"Config AP",      arsenal_config_ap                },
        {"Config Dash",    arsenal_config_dashboard         },
        {"PIN Lock",       arsenal_pin_lock                 },
    };

    // NOTE: background OPSEC monitoring is NOT auto-started on menu entry — it
    // would flip WiFi into STA+promiscuous mode (lighting the WiFi status icon)
    // just for opening the menu. Start it explicitly from the OPSEC tools if wanted.

    addOptionToMainMenu();
    loopOptions(options, MENU_TYPE_SUBMENU, "Arsenal");
}

void ArsenalMenu::wifiArsenalMenu() {
    options = {
        {"Network Scanner",    arsenal_network_scanner          },
        {"Karma Attack",       arsenal_karma_attack             },
        {"DHCP Starvation",    arsenal_dhcp_starvation          },
        {"DNS Spoofer",        arsenal_dns_spoofer              },
#if !LITE_VERSION
        {"Beacon Flood",       arsenal_beacon_flood             },
        {"Selective Deauth",   arsenal_selective_deauth         },
        {"WPA Handshake",      arsenal_wpa_handshake_grabber    },
        {"PMKID Capture",      arsenal_pmkid_capture            },
        {"WiFi Bruteforce",    arsenal_wifi_bruteforce          },
        {"ARP Poisoner",       arsenal_arp_poisoner             },
        {"Auto-Phish Portal",  arsenal_captive_portal_autophish },
        {"Cred Forward",       arsenal_cred_forward             },
#endif
        {"Auth Flood",         arsenal_auth_flood               },
        {"AP Clone Flood",     arsenal_ap_clone_flood           },
#if !LITE_VERSION
        {"SSL Strip Lite",     arsenal_ssl_strip                },
#endif
#if !LITE_VERSION
        {"UPnP Port Opener",   arsenal_upnp_port_opener         },
        {"Default Creds",      arsenal_default_cred_scanner     },
#endif
        {"DNS Tunnel",         arsenal_dns_tunnel               },
        {"WPS PIN Attack",     arsenal_wps_pin_attack           },
        {"Rogue AP Detect",    arsenal_rogue_ap_detector        },
        {"Back",               [this]() { optionsMenu(); }      },
    };
    loopOptions(options, MENU_TYPE_SUBMENU, "WiFi Arsenal");
}

void ArsenalMenu::bleArsenalMenu() {
    options = {
#if !LITE_VERSION
        {"BLE Tracker",        arsenal_ble_tracker              },
        {"BT Name Spammer",    arsenal_bt_name_spammer          },
        {"AirTag Spoofer",     arsenal_airtag_spoofer           },
        {"Audio Jammer",       arsenal_bt_audio_jammer          },
        {"Notif Spoofer",      arsenal_sms_notification_spoofer },
        {"BT Rickroll",        arsenal_bt_audio_rickroll        },
        {"Device Profiler",    arsenal_bt_device_profiler       },
#endif
        {"Back",               [this]() { optionsMenu(); }      },
    };
    loopOptions(options, MENU_TYPE_SUBMENU, "BLE Arsenal");
}

void ArsenalMenu::intelligenceMenu() {
    options = {
        {"OPSEC Monitor",      arsenal_opsec_monitor            },
        {"OUI Lookup",         arsenal_oui_lookup               },
        {"Probe Log",          arsenal_wifi_probe_log           },
        {"Banner Grabber",     arsenal_service_banner_grabber   },
#if !LITE_VERSION
        {"SmartHome Scan",     arsenal_smart_home_scanner       },
#endif
        {"Channel Chart",      arsenal_wifi_channel_chart       },
        {"SSID History",       arsenal_ssid_history_logger      },
        {"Fingerprint",        arsenal_device_fingerprinter     },
#if !LITE_VERSION
        {"People Counter",     arsenal_people_counter           },
#endif
        {"Device Nickname",    arsenal_device_nickname          },
        {"Back",               [this]() { optionsMenu(); }      },
    };
    loopOptions(options, MENU_TYPE_SUBMENU, "Intelligence");
}

void ArsenalMenu::evasionMenu() {
    options = {
        {"MAC Rotator",        arsenal_mac_rotator              },
        {"Channel Hopper",     arsenal_channel_hopper           },
        {"Decoy Traffic",      arsenal_decoy_traffic            },
        {"Identity Cloner",    arsenal_identity_cloner          },
        {"Time Randomizer",    arsenal_time_based_randomizer    },
        {"Back",               [this]() { optionsMenu(); }      },
    };
    loopOptions(options, MENU_TYPE_SUBMENU, "Evasion");
}

void ArsenalMenu::rfMenu() {
    options = {
#if !LITE_VERSION
        {"NRF24 MouseJack",    arsenal_nrf24_mousejack          },
        {"RollJam",            arsenal_rolljam                  },
        {"Doorbell Replay",    arsenal_doorbell_replay          },
        {"Garage Brute Force", arsenal_garage_brute_force       },
        {"Keyfob Logger",      arsenal_car_keyfob_logger        },
#endif
        {"Frequency Scanner",  arsenal_frequency_scanner        },
        {"Flipper Import",     arsenal_flipper_import           },
        {"Back",               [this]() { optionsMenu(); }      },
    };
    loopOptions(options, MENU_TYPE_SUBMENU, "Sub-GHz / RF");
}

void ArsenalMenu::phishingMenu() {
    options = {
        {"Win Update",         arsenal_phish_windows_update     },
        {"WiFi Speed",         arsenal_phish_wifi_speed         },
        {"OAuth Phish",        arsenal_phish_oauth              },
        {"Device Found",       arsenal_phish_device_found       },
        {"Back",               [this]() { optionsMenu(); }      },
    };
    loopOptions(options, MENU_TYPE_SUBMENU, "Phishing Portals");
}

void ArsenalMenu::detectionMenu() {
    options = {
#if !LITE_VERSION
        {"Deauth Detector",    arsenal_deauth_detector          },
        {"Flipper Detector",   arsenal_flipper_detector         },
        {"Hacker Detector",    arsenal_hacker_detector          },
        {"RF Silence",         arsenal_rf_silence_enforcer      },
#endif
        {"Back",               [this]() { optionsMenu(); }      },
    };
    loopOptions(options, MENU_TYPE_SUBMENU, "Detection");
}

void ArsenalMenu::commsMenu() {
    options = {
#if !LITE_VERSION
        {"ESP-NOW Chat",       arsenal_espnow_chat              },
        {"ESP-NOW C2",         arsenal_espnow_c2                },
#endif
#if !LITE_VERSION
        {"Dead Drop Mesh",     arsenal_dead_drop_mesh           },
        {"IR Data Transfer",   arsenal_ir_data_transfer         },
        {"Multi-Device Sync",  arsenal_multi_device_sync        },
#endif
        {"Back",               [this]() { optionsMenu(); }      },
    };
    loopOptions(options, MENU_TYPE_SUBMENU, "Comms");
}

void ArsenalMenu::utilityMenu() {
    options = {
        {"Password Gen",       arsenal_password_generator       },
        {"QR Poisoner",        arsenal_qr_poisoner              },
        {"IR Remote",          ir_remote_app                    },
#if !LITE_VERSION
        {"NFC Biz Card",       arsenal_nfc_business_card        },
#endif
        {"Attack Stats",       arsenal_attack_stats             },
        {"Back",               [this]() { optionsMenu(); }      },
    };
    loopOptions(options, MENU_TYPE_SUBMENU, "Utility");
}

void ArsenalMenu::jamAllMenu() {
    arsenal_jam_all();
}

void ArsenalMenu::dashboardMenu() {
#if !LITE_VERSION
    arsenal_remote_dashboard();
#endif
}

void ArsenalMenu::drawIcon(float scale) {
    clearIconArea();

    // Crosshair/target icon - unique to Arsenal
    int r1 = scale * 22;  // outer ring
    int r2 = scale * 14;  // inner ring
    int r3 = scale * 4;   // center dot
    int lineLen = scale * 28;

    // Outer ring
    tft.drawCircle(iconCenterX, iconCenterY, r1, bruceConfig.priColor);
    // Inner ring
    tft.drawCircle(iconCenterX, iconCenterY, r2, bruceConfig.priColor);
    // Center dot
    tft.fillCircle(iconCenterX, iconCenterY, r3, bruceConfig.priColor);

    // Crosshair lines
    // Top
    tft.drawLine(iconCenterX, iconCenterY - lineLen, iconCenterX, iconCenterY - r1 - 2, bruceConfig.priColor);
    // Bottom
    tft.drawLine(iconCenterX, iconCenterY + r1 + 2, iconCenterX, iconCenterY + lineLen, bruceConfig.priColor);
    // Left
    tft.drawLine(iconCenterX - lineLen, iconCenterY, iconCenterX - r1 - 2, iconCenterY, bruceConfig.priColor);
    // Right
    tft.drawLine(iconCenterX + r1 + 2, iconCenterY, iconCenterX + lineLen, iconCenterY, bruceConfig.priColor);
}
