window.addEventListener('DOMContentLoaded', () => {

    let webui_connected = false;
    let drive_letters = null;

    function wait_webui(retry, callback) {

        if (typeof webui === 'undefined') {
            console.error('WebUi not defined.');
            return;
        }

        if (webui.isConnected()) {
            console.log("Webui connected");
            webui_connected = true;
            if (typeof callback !== 'undefined')
                callback();
            return;
        } else if (retry > 0) {
            console.log("Waiting for login...")
            setTimeout(() => wait_webui(retry - 1, callback), 500);
        } else {
            console.log("Too much tries, abort.");
            return;
        }

    }

    function when_webui_is_connected(){

        if( !webui_connected ) return;

        if( window.location.href.includes( "index.html" ) ){

            handle_warnings_button();

        }

        if( window.location.href.includes( "select_drive.html" ) ) {

            // Get drive letters available.
            webui.call('get_drives')
                .then(response => {
                    console.log( response );
                    drive_letters = JSON.parse(response);
                    console.log(drive_letters);
                    drive_letters_as_select();
                });

        }

        if( window.location.href.includes( "wii_mac_address.html" ) ) {

           valid_mac_address();

        }

        if( window.location.href.includes( "wii_version_region.html" ) ) {

            valid_wii_version_region();

        }

        handle_explanations();

    }

    function handle_warnings_button(){

        const elements = { "warn_clear_cache": "clear_cache" };

        for( const [key, value] of Object.entries(elements)){
            document.getElementById(key).onclick = function(e){

                e.preventDefault();
                if( confirm( "Êtes-vous sûr de vouloir effectuer cette action ?" ) )
                    webui.call( value );
            }
        }

    }

    function handle_explanations(){

        const explanations = document.getElementById( 'explanation_content' );
        const arrow = document.getElementById('explanation_arrow');

        document.getElementById( 'explanation_show' ).onclick = function(e){

            if( explanations.style.display == "none" ){
                explanations.style.display = "block";
                arrow.innerHTML = "▼"
            } else {
                explanations.style.display = "none";
                arrow.innerHTML = "►"
            }

        }
    }

    function drive_letters_as_select(){

        const selector = document.getElementById("drive_selector");

        drive_letters.forEach( (letter) => {
            const opt = document.createElement("option");
            opt.text = letter; opt.value = letter;
            selector.add(opt, null);
        });

        document.getElementById( "valid_drive_letter_selection" ).onclick = function( e ){

           if( typeof selector.value == "undefined" || selector.value == "" )
               return;

           webui.call("continue", selector.value);
           // window.close();

        }

    }

    function valid_mac_address(){

        const input_mac = document.getElementById( "mac_address" );
        document.getElementById( "valid_mac_address" ).onclick = function( e ){

            if( typeof input_mac === 'undefined' || input_mac.value == "" )
                return;

            webui.call('verify_mac_address', input_mac.value )
                .then(response => {
                    console.log( response );
                    if (response == true){
                        webui.call("continue", input_mac.value );
                    }
                });
        }
    }

    function valid_wii_version_region(){

        const version_selector = document.getElementById("version_selector");
        const region_selector = document.getElementById("region_selector");

        document.getElementById( "valid_version_region" ).onclick = function( e ){

            if( typeof version_selector.value == "undefined" || version_selector.value == "" || typeof region_selector.value == "undefined" || region_selector.value == ""  )
                return;

            webui.call("continue", version_selector.value + region_selector.value );
            // window.close();

        }
    }

    wait_webui( 10, when_webui_is_connected );

});