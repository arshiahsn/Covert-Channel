# Covert-Channel
Covert Storage Channel using Object Existence
File attributes are storage objects that are indirectly writable. Storage channels also include any items of information about the file that can be deduced by a process. For example, the fact that a given file exists is a bit of information; and even if you have no access to any of a file’s attributes, you may still be able to infer whether a particular file exists. A simple way to do so would be to try to access the file and check the returned status condition. Some systems obligingly tell you whether your problem is file does not exist or you have no access to the fi1e. If the system can support ten file creations or deletions per second, the Trojan horse can communicate ten bits of information per second.
If the system does not tell you directly whether a file inaccessible to you exists, you might try to create a new file with the same name as that file. If the system gives you a namedup1ication or other error, you will have confirmed that the file already exists. If the system allows you to create and use the new file, you will have established that the file did not previously exist.
The single bit of information about existence of a file may not seem like much information, but some systems strive to provide high-speed file creation and deletion. Thus, though the information channel is narrow, its bandwidth can be high, especially if multiple files are used.
==========================================================================================================================================================================================================================================================
1. This project contains two files: A sender and a receiver
2. Compile both files using any C/C++ compiler such as (gcc, visualC, ...)
3. Run each programme seperately.
4. Sender asks you for input, use any desired ascii strings.
5. Sender starts broadcasting the message using method explained later. Each message starts and ends with a preemtion block containing two characters: '%' and '$' ('%$' for start and '$%' for end of message)  
6. Receiver starts sensing by detecting characters '%' and '$' consecutively.
7. Receiver synchronizes itself with sender and captures message.
8. When message fully captured, receiver signals the sender to quit.
9. Receiver terminates itself.
==========================================================================================================================================================================================================================================================
This project works only on microsoft windows.
The bandwidth of covert channel is set to 1bit per second, which can be changed to any desired speed according to system's support for number of file creation and deletions on a second. Default address is set to C:\\
For each bit of message, existence of the folder indicates 1 and absence of the folder indicates 0.
Sender converts the message to ascii, character by character from the begging and creates or deletes a folder on default address according to the related message bit. Receiver checks whether the folder exists or not and buffers 0 or 1 according to the result. Receiver converts each 8 bits to an ascii character. If receiver captures a preemtion block, it signals the sender that it has received the message using the same method, and then it quits.
