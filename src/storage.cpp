#include "../include/storage.h"
#include "../include/globals.h"
#include "../include/utils.h"

#include <filesystem>
#include <iostream>
#include <zip.h>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#endif

namespace fs = std::filesystem;

namespace Storage {

    /**
     * Return removable drives available on the computer.
     *
     * @return
     */
    std::vector<std::string> return_available_removable_drives() {

        std::vector<std::string> removable_drives = {};

        #ifdef _WIN32

            DWORD available_drives = GetLogicalDrives();
            if ( available_drives == 0 )
                return removable_drives;

            for(char letter = 'A'; letter <= 'Z'; ++letter ) {
                if ( available_drives & (1 << letter - 'A') ) {

                    std::string current_drive = std::string(1, letter) + ":\\";
                    UINT drive_type = GetDriveTypeA(current_drive.c_str() );

                    if ( drive_type == DRIVE_REMOVABLE )
                        removable_drives.push_back(current_drive);
                }
            }

            log_info( "Amovible drives listed: " + std::to_string(removable_drives.size()) );

        #endif

        return removable_drives;

    }

    /**
     * Get recursively files of a specified folder.
     *
     * @param folder
     * @return
     */
    std::vector<std::string> get_file_list_recursively( std::string folder ) {

        std::vector<std::string> files;

        try {
            for (const auto& entry : fs::recursive_directory_iterator(folder)) {
                if (fs::is_regular_file(entry.path())) {
                    fs::path relative = entry.path().lexically_relative(folder);
                    files.push_back( relative.string() );
                    log_info( "[Get File List] List: " + relative.string() );
                }
            }
        } catch (const fs::filesystem_error& e) {
            // Nothing.
        }

        return files;

    }

    /**
     * Verify if temp folder exists, then create it.
     */
    void temp_folder_exists() {

        if (!fs::exists( STELARE_TEMP_FOLDER ) )
            fs::create_directory( STELARE_TEMP_FOLDER );

    }

    /**
     * Download a file in the TEMP folder.
     *
     * @param url
     * @param filename - Filename in the temp folder.
     * @return
     */
    int download_in_temp_folder( std::string url, std::string filename ) {

        temp_folder_exists();

        std::string save_path = fs::current_path().string() + "\\" + STELARE_TEMP_FOLDER + "\\" + filename;

        #ifdef _WIN32
            log_info("[Download] Try Windows download from: " + url + " ;to: " + save_path );
            if ( URLDownloadToFile(NULL, url.c_str(), save_path.c_str(), 0, NULL) == S_OK )
                return Codes::OK; // Download good.
            return STORAGE__ERR_CANTDL; // Download failed.
        #endif

        return Codes::OK; // What is your system ?

    }

    /**
     * Extract every file from a ZIP archive.
     *
     * @param zip_path_temp - Relative path from temp folder.
     * @param output_folder_in_temp - Output folder in temp folder. Leave empty to extract in the temp root.
     * @return
     */
    int extract_all_in_temp_folder( std::string zip_path_temp, std::string output_folder_in_temp ) {

        temp_folder_exists();

        log_info( "[Extract All] Try Extract: " + zip_path_temp + " ;to: " + output_folder_in_temp );

        int errors = 0;
        std::string input = fs::current_path().string() + "\\" + STELARE_TEMP_FOLDER + "\\" + zip_path_temp;

        zip* archive = zip_open( input.c_str(), ZIP_RDONLY, &errors );
        if ( !archive )
            return errors;

        zip_int64_t total_size = zip_get_num_entries(archive, 0);
        std::string output = fs::current_path().string() + "\\" + STELARE_TEMP_FOLDER + "\\" + output_folder_in_temp;

        for ( zip_uint64_t i = 0; i < total_size; ++i ) {

            struct zip_stat stat;
            zip_stat_init( &stat );
            if (zip_stat_index(archive, i, 0, &stat) == 0) {
                if (stat.name[strlen(stat.name) - 1] == '/' ) {
                    fs::create_directories( output + "/" + stat.name );
                    continue;
                }

                zip_file* zf = zip_fopen_index( archive, i, 0 );
                if ( !zf )
                    continue;

                std::string out_path = output + "/" + stat.name;
                fs::create_directories( fs::path(out_path).parent_path() );

                std::ofstream out(out_path, std::ios::binary);
                std::vector<char> buffer(stat.size);

                zip_fread(zf,buffer.data(),buffer.size() );
                out.write(buffer.data(),buffer.size());
                out.close();

                zip_fclose(zf);

            }
        }

        zip_close( archive );
        return Codes::OK;

    }

    /**
     *
     * @param zip_path_temp Relative path from temp folder.
     * @param file_name_in_zip Filename of the file that need to be extracted in the archive.
     * @param output_folder_in_temp_w_filename Output of the file in the temp folder with the filename !
     * @return
     */
    int extract_file_in_temp_folder( std::string zip_path_temp, std::string file_name_in_zip, std::string output_folder_in_temp_w_filename ) {

        log_info( "[Extract File] Try Extract: " + zip_path_temp + " (" + file_name_in_zip + ");to: " + output_folder_in_temp_w_filename );

        temp_folder_exists();

        int errors = 0;
        std::string input = fs::current_path().string() + "\\" + STELARE_TEMP_FOLDER + "\\" + zip_path_temp;

        zip* archive = zip_open( input.c_str(), ZIP_RDONLY, &errors );
        if ( !archive )
            return errors;

        zip_stat_t stat;
        if ( zip_stat( archive, file_name_in_zip.c_str(), 0, &stat ) != 0 ) {
            zip_close(archive);
            return Codes::Cant_Open;
        }

        zip_file* zf = zip_fopen(archive, file_name_in_zip.c_str(), 0 );
        if ( !zf ) {
            zip_close(archive);
            return Codes::Cant_Open;
        }

        std::string out_path = fs::current_path().string() + "\\" + STELARE_TEMP_FOLDER + "\\" + output_folder_in_temp_w_filename;
        fs::create_directories( fs::path(out_path).parent_path() );

        std::ofstream out(out_path, std::ios::binary);
        std::vector<char> buffer(stat.size);

        zip_fread(zf,buffer.data(),buffer.size() );
        out.write(buffer.data(),buffer.size());
        out.close();

        zip_fclose(zf);
        zip_close(archive);
        return Codes::OK;

    }

    /**
     *
     * @param zip_path_temp Relative path from temp folder.
     * @param file_name_in_zip Filename of the file that need to be extracted in the archive.
     * @param output_folder_in_temp_w_filename Output of the file in the temp folder with the filename !
     * @return
     */
    int extract_folder_in_temp_folder(std::string zip_path_temp, std::string file_name_in_zip, std::string output_folder_in_temp_w_filename) {

        log_info( "[Extract Folder] Try Extract: " + zip_path_temp + " (" + file_name_in_zip + ");to: " + output_folder_in_temp_w_filename );

        temp_folder_exists();

        int errors = 0;
        std::string input = fs::current_path().string() + "\\" + STELARE_TEMP_FOLDER + "\\" + zip_path_temp;

        zip* archive = zip_open(input.c_str(), ZIP_RDONLY, &errors);
        if (!archive)
            return errors;

        zip_int64_t num_entries = zip_get_num_entries(archive, 0);
        bool found = false;

        for (zip_uint64_t i = 0; i < num_entries; ++i) {
            zip_stat_t stat;
            if (zip_stat_index(archive, i, 0, &stat) != 0)
                continue;

            std::string entry_name = stat.name;

            if (entry_name == file_name_in_zip || entry_name.rfind(file_name_in_zip + "/", 0) == 0) {
                found = true;

                zip_file* zf = zip_fopen_index(archive, i, 0);
                if (!zf)
                    continue;

                std::string relative_path = entry_name.substr(file_name_in_zip.length());
                std::string out_path = fs::current_path().string() + "\\" + STELARE_TEMP_FOLDER + "\\" + output_folder_in_temp_w_filename;

                if (entry_name != file_name_in_zip) {
                    out_path += "\\" + relative_path;
                }

                fs::create_directories(fs::path(out_path).parent_path());

                if (entry_name.back() != '/') {
                    std::ofstream out(out_path, std::ios::binary);
                    std::vector<char> buffer(stat.size);

                    zip_fread(zf, buffer.data(), buffer.size());
                    out.write(buffer.data(), buffer.size());
                    out.close();
                }

                zip_fclose(zf);
            }
        }

        zip_close(archive);

        if (!found)
            return Codes::Cant_Open;

        return Codes::OK;
    }

    /**
     * Do a backup of a file in the backup folder.
     * @param drive_path - Current selected drive.
     * @param files_to_backup - Files if exists needed to be backup.
     * @return
     */
    int do_a_backup( std::string drive_path, std::vector<std::string> files_to_backup ) {

        if (!fs::exists( STELARE_BACKUP_FOLDER ) )
            fs::create_directory( STELARE_BACKUP_FOLDER );

        std::string complete_path = "";

        for ( int i = 0; i < files_to_backup.size(); i++ ) {
            complete_path = drive_path + files_to_backup[i];
            if ( fs::exists( complete_path.c_str() ) ) {
                fs::create_directories( fs::path( fs::current_path().string() + "\\" + STELARE_BACKUP_FOLDER + "\\" + files_to_backup[i] ).parent_path() );
                fs::copy( complete_path, fs::current_path().string() + "\\" + STELARE_BACKUP_FOLDER + "\\" + files_to_backup[i], fs::copy_options::update_existing );
                log_info( "[Backup] " + complete_path + " to " + STELARE_BACKUP_FOLDER );
            }
        }

        return 0;
    }

    /**
     *
     * @param drive_path - Drive letter
     * @param drive_folder - Folder to extract in the selected drive. Leave empty for root.
     * @param temp_file - File path in the temp folder that need to be copied.
     * @return
     */
    int do_a_backup_and_copy_file_to_drive( std::string drive_path, std::string drive_folder, std::string temp_file ) {

        std::string filename = fs::current_path().string() + "\\" + STELARE_TEMP_FOLDER + "\\" + temp_file;
        std::string drive_path_full = drive_path + drive_folder;
        if ( fs::exists( filename ) ) {
            do_a_backup(drive_path_full, {temp_file} );
            fs::create_directories( fs::path( drive_path_full + temp_file ).parent_path() );
            log_info( "[Copy] " + fs::current_path().string() + "\\" + STELARE_TEMP_FOLDER + "\\" + temp_file + " to " + drive_path_full + temp_file );
            fs::copy( fs::current_path().string() + "\\" + STELARE_TEMP_FOLDER + "\\" + temp_file, drive_path_full +  temp_file, fs::copy_options::overwrite_existing );
            return Codes::OK;
        }
        return Codes::Cant_Open;
    }

/**
 *
 * @param drive_path - Drive letter
 * @param drive_folder - Folder to extract in the selected drive. Leave empty for root.
 * @param temp_folder - File path in the temp folder that need to be copied.
 * @return
 */
    int do_a_backup_and_copy_folder_to_drive( std::string drive_path, std::string drive_folder, std::string temp_folder ) {

        std::vector<std::string> files_in_temp_folder = get_file_list_recursively( fs::current_path().string() + "\\" + STORAGE_TEMP_FOLDER + "\\" + temp_folder );
        std::string drive_path_full = drive_path + drive_folder;
        do_a_backup(drive_path_full, files_in_temp_folder);
        for ( int j = 0; j < files_in_temp_folder.size(); j++ ) {
            fs::create_directories( fs::path( drive_path_full + files_in_temp_folder[j] ).parent_path() );
            log_info( "[Copy] " + fs::current_path().string() + "\\" + STORAGE_TEMP_FOLDER + "\\" + temp_folder + "/" + files_in_temp_folder[j] + " to " + drive_path_full + files_in_temp_folder[j] );
            fs::copy( fs::current_path().string() + "\\" + STORAGE_TEMP_FOLDER + "\\" + temp_folder + "/" + files_in_temp_folder[j], drive_path_full + files_in_temp_folder[j], fs::copy_options::update_existing );
        }
        return Codes::OK;

    }

    /**
     *
     * @param temp_file Temp file that need to be moved in executables folder.
     * @return
     */
    int move_to_executables( std::string temp_file ) {

        if (!fs::exists( STELARE_EXE_FOLDER ) )
            fs::create_directory( STELARE_EXE_FOLDER );

        try {
            fs::rename( fs::current_path().string() + "\\" + STELARE_TEMP_FOLDER + "\\" + temp_file, fs::current_path().string() + "\\" + STELARE_EXE_FOLDER + "\\" + temp_file );
        } catch (const fs::filesystem_error& e) {
            // Nothing.
        }

        return 0;

    }

}