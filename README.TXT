Large integer object is designed to be a vector of bytes.
If the value of the object happen to require more byte to represent, then more bytes will be added into the vector.
operators are overloaded to handle calculations on the object.
Swapping value would be simplier if we use pointer of vector for object's attribute.
The decimal parsing uses a helper class implemented in the largeInt class

Run the program: open the Developer Command Prompt for VSCode -> run 'cl main.cpp largeInt.cpp \o ./main.exe'

EXP Gained:
we can just build largeInt.obj and reuse it when create the executable files: 'cl largeInt.cpp' -> 'cl main.cpp largeInt.obj'