#ifndef INPUT_H
#define INPUT_H

#include <string>

namespace Snaze{

    /// Receives the name of the file by the terminal
    class Input{
        private:
            std::string file_name; //!< Receives the file name
        public:
            /// Constructor
            Input(int argc, char **argv)
            : file_name("../maze_files/game1.dat"){
                if(argc == 1) return;
                std::string param(argv[1]);
                file_name = param;
            }
            /// Destructor
            ~Input(){/*empty*/};
            /*!
            @return The file_name attibute.
            */
            std::string get_file_name(){
                return this->file_name;
            };
    };

}
#endif
