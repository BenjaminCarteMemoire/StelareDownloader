#ifndef _STORAGE_H_
#define _STORAGE_H_

#include <iostream>
#include <vector>

namespace Storage {

    enum Codes {
        OK = 0,
        Cant_Open = 59,
        WTF = 69
    };

    bool verify_mac_address( std::string mac_address );

    std::vector<std::string> return_available_removable_drives();

    std::vector<std::string> get_file_list_recursively( std::string folder );

    void temp_folder_exists();

    int download_in_temp_folder( std::string url, std::string filename );

    int extract_all_in_temp_folder( std::string zip_path_temp, std::string output_folder_in_temp );

    int extract_file_in_temp_folder( std::string zip_path_temp, std::string file_name_in_zip, std::string output_folder_in_temp_w_filename );

    int extract_folder_in_temp_folder(std::string zip_path_temp, std::string file_name_in_zip, std::string output_folder_in_temp_w_filename);

    int do_a_backup( std::string drive_path, std::vector<std::string> files_to_backup );

    int do_a_backup_and_copy_file_to_drive( std::string drive_path, std::string drive_folder, std::string temp_file );

    int do_a_backup_and_copy_folder_to_drive( std::string drive_path, std::string drive_folder, std::string temp_folder );

    int move_to_executables( std::string temp_file );

}

#endif
