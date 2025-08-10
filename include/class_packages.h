#pragma once

#include <functional>
#include <vector>
#include <map>

#ifndef STELARE_CLI

#include "../lib/webui/include/webui.hpp"

#endif

class Package {

    public:

        /**
         * ID name of the package.
         */
        std::string name;

        /**
         * Visual name of the package.
         */
        std::string pretty_name;

        #ifndef STELARE_CLI

        /**
         * Callbacks needed to be called in order.
         *
         * Vector of Window->event functions.
         */
        std::vector<std::function<void( webui::window::event* e )>> callbacks = {};

        #endif

        /**
         * All files needed to be downloaded.
         *
         * key : Filename
         * value : URL
         */
        std::map<std::string, std::string> downloads = {};

        /**
         * All files after download needed to be extracted every files.
         *
         * key : File path (IN TEMP FOLDER AS BASE)
         * value : Output path in the TEMP folder.
         */
        std::map<std::string, std::string> extract_all = {};

        /**
         * All archives after download needed to be extracted but only a single file.
         *
         * key : File Path in the temp folder.
         * value :
         *        key : File path in the archive for the file needed to be extracted.
         *        value : Output folder in the temp folder WITH FILENAME.
         */
        std::map<std::string, std::pair<std::string, std::string>> extract_file = {};

        /**
         * All archives after download needed to be extracted but only a single folder.
         *
         * key : File Path in the temp folder.
         * value :
         *        key : File path in the archive for the file needed to be extracted.
         *        value : Output folder in the temp folder WITH FILENAME.
         */
        std::map<std::string, std::pair<std::string, std::string>> extract_folder = {};

        /**
         * All files needed to be moved from TEMP to EXECUTABLES
         */
        std::vector<std::string> move_to_executables = {};

        /**
         * All files in temp needed to be moved in the drive.
         *
         * key : File path in TEMP folder.
         * value : Output in the drive (Without the letter).
         */
        std::map<std::string, std::string> move_to_drive_files = {};

        /**
         * All folders in temp needed to be moved in the drive.
         *
         * key : File path in TEMP folder.
         * value : Output in the drive (Without the letter).
         */
        std::map<std::string, std::string> move_to_drive_folders = {};

        Package(

            std::string package_name,
            std::string package_pretty_name

        );

        void add_in_package_global();
        void automatic_process();

};

