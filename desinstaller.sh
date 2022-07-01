#!/usr/bash

green=`tput setaf 2`
bold=`tput bold`
reset=`tput sgr0`

echo "${green}${bold}\n********************************************************************************${reset}"
echo "${green}${bold}*****************************DESINSTALADOR*****************************************${reset}"
echo "${green}${bold}********************************************************************************${reset}"

for arg in "$@"
do
    case $arg in

        --qt)
        shift
        echo "${green}${bold}Desinstalando las dependencias de qt...${reset}"

        echo "${green}Desinstalando 'qt5'...${reset}"
        sudo apt-get remove qt5-default -y

        echo "${green}Desinstalando 'libqt5multimedia5-plugnins'...${reset}"
        sudo apt-get remove libqt5multimedia5-plugins -y
        
        ;;



        --yaml)
        shift
        echo "${green}${bold}Desinstalando las dependencias de yaml-cpp...${reset}"

        sudo apt-get remove libyaml-cpp-dev -y

        ;;



        --sdl)
        shift
        echo "${green}${bold}Desinstalando las dependencias de sdl2...${reset}"

        echo "${green}Desinstalando 'libsdl2-dev'...${reset}"
        sudo apt-get remove libsdl2-dev -y

        echo "${green}Desinstalando 'libsdl2-image-dev'...${reset}"
        sudo apt-get remove libsdl2-image-dev -y

        echo "${green}Desinstalando 'libsdl2-gfx-dev'...${reset}"
        sudo apt-get remove libsdl2-gfx-dev -y

        echo "${green}Desinstalando 'libsdl2-mixer-dev'...${reset}"
        sudo apt-get remove libsdl2-mixer-dev -y
        
        ;;



        --cpp)
        shift
        echo "${green}${bold}Desinstalando las dependencias cpp...${reset}"

        echo "${green}Desinstalando 'clang'...${reset}"
        sudo apt-get remove clang -y 

        echo "${green}Desinstalando 'make'...${reset}"
        sudo apt-get remove make -y 

        echo "${green}Desinstalando 'cmake'...${reset}"
        sudo apt-get remove cmake -y

        echo "${green}Desinstalando 'build-essential'...${reset}"
        sudo apt-get remove build-essential -y

        ;;


        --repo)
        shift
        echo "${green}${bold}Borrando el repositorio...${reset}"
        cd ..
        rm Dune_TP3
        ;;

	    --dune)
        shift
        echo "${green}${bold}Desinstalando DUNE 2000...${reset}"
    	sudo rm /usr/bin/client_interface
    	sudo rm /usr/bin/editor_interface
    	sudo rm /usr/bin/server
        ;;

        --all)
        shift

        echo "${green}Desinstalando 'qt5'...${reset}"
        sudo apt-get remove qt5-default -y

        echo "${green}Desinstalando 'libqt5multimedia5-plugnins'...${reset}"
        sudo apt-get remove libqt5multimedia5-plugins -y
        
        echo "${green}Desinstalando las dependencias de yaml-cpp...${reset}"
        sudo apt-get remove libyaml-cpp-dev -y

        echo "${green}Desinstalando 'libsdl2-dev'...${reset}"
        sudo apt-get remove libsdl2-dev -y

        echo "${green}Desinstalando 'libsdl2-image-dev'...${reset}"
        sudo apt-get remove libsdl2-image-dev -y

        echo "${green}Desinstalando 'libsdl2-gfx-dev'...${reset}"
        sudo apt-get remove libsdl2-gfx-dev -y

        echo "${green}Desinstalando 'libsdl2-mixer-dev'...${reset}"
        sudo apt-get remove libsdl2-mixer-dev -y
        
        echo "${green}Desinstalando 'libsdl2-ttf-dev'...${reset}"
        sudo apt-get remove libsdl2-mixer-dev -y

        echo "${green}Desinstalando 'clang'...${reset}"
        sudo apt-get remove clang -y 

        echo "${green}Desinstalando 'make'...${reset}"
        sudo apt-get remove make -y 

        echo "${green}Desinstalando 'cmake'...${reset}"
        sudo apt-get remove cmake -y

        echo "${green}Desinstalando 'build-essential'...${reset}"
        sudo apt-get remove build-essential -y

        cd ..
        rmdir Dune_TP3

        echo "${green}${bold}Desinstalando DUNE 2000...${reset}"
    	sudo rm /usr/bin/client_interface
    	sudo rm /usr/bin/editor_interface
    	sudo rm /usr/bin/server

        ;;



    esac
done