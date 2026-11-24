

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <chrono>
#include <thread>
#include <cctype>
#include <fstream>
#include <filesystem>

/*
Light Blue: #5BCEFA (RGB: 91, 206, 250)
Light Pink: #F5A9B8 (RGB: 245, 169, 184)
White: #FFFFFF (RGB: 255, 255, 255) ⁠
*/

#ifdef _WIN32
    #include <windows.h>
#elif __APPLE__
    #include <mach-o/dyld.h>
#elif __linux__
    #include <unistd.h>
#endif

namespace fs = std::filesystem;

fs::path get_dir() {

    #ifdef _WIN32

        wchar_t buf[MAX_PATH];
        GetModuleFileNameW(nullptr, buf, MAX_PATH);

        return fs::path(buf).parent_path();

    #elif __APPLE__

        char buf[4096];
        uint32_t size = sizeof(buf);
        _NSGetExecutablePath(buf, &size);
        char resolved[4096];
        realpath(buf, resolved);

        return fs::path(resolved).parent_path();

    #elif __linux__

        char buf[4096];
        ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
        buf[len] = '\0';

        return fs::path(buf).parent_path();

    #endif

};   

fs::path g_path = get_dir();
std::string g_activefile = "out.txt";

int g_cmdcount = 0;
int g_whycount = 0;
bool g_whycountup = true;
int g_ciscount = 0;

std::vector<std::string> split(const std::string& s) { //Function def. I guess.

    std::vector<std::string> out; //Return this eventually.
    std::string that_string;
    
    char qchar = 0; //That's not a quote character.
    bool skip = false; //Skip a backslash.

    for (char c : s) {

        if (skip) {
            skip = false;
            that_string += c;
        } 
        
        else if (c == '\\') {
            skip = true;
        } 
        
        else if (!qchar && (c == '"' || c == '\'')) { 
            qchar = c;
        } 
        
        else if (qchar && c == qchar) {
            qchar = 0;
        } 
        
        else if (!qchar && std::isspace(c)) {

            if (!that_string.empty()) {
                out.push_back(that_string);
                that_string.clear();
            }
            
        } 
        
        else {
            that_string += c;
        }

    }

    if (!that_string.empty()) {
        out.push_back(that_string); //Most of this is magic that I do not quite understand yet, I try to, I get the basic idea, which is why I can do this.
    }

    skip = false;
    qchar = 0; //Straight up just wasted two lines, hey, I know that I do not need it, but I have a feeling that future me is not fully idiot proof.
    return out;

};

struct {

    std::vector<double> listwd(std::vector<std::string> inpvector) {

        std::vector<double> outptlistwd;

        for (int x = 2; x < inpvector.size(); x++) { //Command syntax
            outptlistwd.push_back(std::stod(inpvector[x])); //No error handling yet.
        }

        return outptlistwd;
    }

    void add(std::vector<double> inpnums) {

        double outp = 0.0;

        for (int x = 0; x < inpnums.size(); x++) {
            outp += inpnums[x];
        }

        std::cout << outp;
    }

    void multiply(std::vector<double> inpnums) {
        
    }

} maethfunc;

void clear(std::string clear_option) {

    if (clear_option != "sbb" && clear_option != "" && clear_option != "nuke") {

        std::cout << "\nReturned to sender.\n\n";
        return;

    }

    std::cout << "\033[2J\033[1;1H";

    if (clear_option == "sbb") {
        std::cout << "\033[3J";
    }

    else if (clear_option == "nuke") {
        std::cout << "\033[3J\033c";
    }

}

void why(std::string why_input) {

    std::vector<std::string> answers = {"Yes.", "I said yes.", "You're still there?", "Fine, yesn't.", "OH, IT IS YOU AGAIN??", "I swear...", "...", "Fuck you", "Because I wanted to, I did not want to need to write a while paragraph abotu why I wanted to, so you can be happy with what you get from this sentence that for some reason still fits within the source code, I love writing long strings in lists to be honest. HELP, I'M STUCK HERE, AAAAAAAAHHHHH-", "HELP", "Oh...", "..."};
    std::vector<std::string> alt_answers = {"Well, it is quite interesting... I don't know why \"this\".", "Please stop asking.", "Hell no.", "Yeah, I will not answer that.", "..."};
    
    std::cout << "\n";

    if (why_input == "") {

        if (0 <= g_whycount && g_whycount < answers.size() && g_whycountup) {
            std::cout << answers[g_whycount];
            g_whycount++;
        }

        else if (g_whycountup) {
            std::cout << "ERROR";
            g_whycount++;
        } 

        else {
            std::cout << "This is a meaningless link: https://www.youtube.com/watch?v=dQw4w9WgXcQ";
        }

    }

    std::cout << "\n\n";

}

void echos() {

    std::cout << "\nEcho\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "\nEcho...\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "\nEch....\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "\nEch......\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "\nEc.......\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "\nE..........\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    for (int x = 0; x < 32; x++) {
        std::cout << ".";
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "\n\nBOO\n\n";

}

void help() {

    std::cout << "\n";
    std::cout << "why - tells you why\n\n";
    std::cout << "cls - this does stuff, try it.\n\n";
    std::cout << "clear - clears the terminal, optionally use 'sbb' or 'nuke' appended to it\n\n";
    std::cout << "echo - echo string\n\n        Modes: -c, -f\n\n        Correct syntax: echo (-c c/-f) <filename | only for -f> \"message\"\n\n";

}

void echo(std::string mode, std::string msg) {
    
    if (mode != "-c" && mode != "-f") {
        std::cout << "\nInvalid mode(s)\n\n";
        return;
    }

    if (mode == "-c") {
        std::cout << "\n" + msg + "\n\n";
    }

    else if (mode == "-f") {

        std::ofstream file (g_path / g_activefile, std::ios::app);
        file << msg << "\n";
        file.close();
        std::cout << "\nWritten to: " << g_path << g_activefile << "\n\n";

    }

}

void cvar(std::string choice) {

    if (choice == "*" || choice == "all") {

        std::cout << "\nActive Path:        ";
        std::cout << g_path;
        std::cout << "\nActive File:        ";
        std::cout << g_activefile;
        std::cout << "\nCommand Count:      ";
        std::cout << g_cmdcount;

    }

    else if (choice == "whycount") {
        std::cout << "\nWhy Count:          ";
        std::cout << g_whycount;
    }

    else if (choice == "cmdcount" || choice == "commandcount") {
        std::cout << "\nCommand Count:      ";
        std::cout << g_cmdcount;
    }

    else if (choice == "path" || choice == "activepath") {
        std::cout << "\nActive Path:        ";
        std::cout << g_path;
    }

    else if (choice == "file" || choice == "activefile") {
        std::cout << "\nActive File:        ";
        std::cout << g_activefile;
    }

    else if (choice == "ciscount") {
        std::cout << "\nCis Count:          ";
        std::cout << g_ciscount;
    }

    else if (choice == "countupwhy" || choice == "whycountup" || choice == "countupwhycount" || choice == "countwhy") {
        std::cout << "\nCount Why";
        std::cout << g_whycountup;
    }

    std::cout << "\n\n";

}

void setvar(std::string choice, std::string contents) {

    if (choice == "whycount") {
        
    }

    else if (choice == "cmdcount" || choice == "commandcount") {
        
    }

    else if (choice == "path" || choice == "activepath") {
        
    }

    else if (choice == "file" || choice == "activefile") {
        
    }

    else if (choice == "ciscount") {

    }

    else if (choice == "countupwhy" || choice == "whycountup" || choice == "countupwhycount" || choice == "countwhy") {
        
    }

}

void check_cmd(std::string input) {

    std::string cmd;
    std::vector<std::string> arguments = split(input);

    if (arguments.empty()) {
        return;
    }

    cmd = arguments[0];

    if (cmd == "help") {
        help();
    }

    else if (cmd == "why") {

        if (arguments.size() > 1) {
            why(arguments[1]);
        }
        
        else {
            why("");
        }

    }

    else if (cmd == "whz") {
        std::cout << "\nDid you switch keyboard layouts again?\n\n";
    }

    else if (cmd == "cis") {

        if (g_ciscount == 0) {
            std::cout << "\nDid you mean cls? I mean, I don't blame you for saying that to me, that could mean you're nb, trans or just straight up cis.\n\n";
            g_ciscount++;
        }
        
        else if(g_ciscount == 1) {
            std::cout << "\nNah, not again, just do cls.\n\n";
            g_ciscount++;
        }

        else if (g_ciscount == 2) {
            std::cout << "\nFine. I get it.\n\n";
            g_ciscount++;
        }

        else {
            std::cout << "\nI GET IT.\n\n";
        }

    }

    else if (cmd == "echos") {
        echos();
    }

    else if (cmd == "clear") {

        if (arguments.size() > 1) {
            clear(arguments[1]);
        }

        else {
            clear("");
        }

    }

    else if (cmd == "echo") {

        if (arguments.size() > 2) {
            echo(arguments[1], arguments[2]);
        }

        else if (arguments.size() == 2) {
            echo(arguments[1], "You sure? Try again next time.");
        }

        else {
            std::cout << "\nGenuinely, what's wrong with you?\n\n";
        }
        
    }

    else if (cmd == "cvar" || cmd == "checkvar" || cmd == "checkvariable") {
        
        if (arguments.size() > 1) {
            cvar(arguments[1]);
        }

        else {
            std::cout << "\nHow did you even think this would work?\n\n";
        }

    }

    else if (cmd == "kms") {
        std::cout << "\nDon't. Just don't. If you really are considering it, there is help to get.\n\n";
    }

    else if (cmd == "notcis") {
        std::cout << "\n" << g_cmdcount << "\n\nOk.\n\n";
    }
}

int main(void) {

    std::string input;
    
    while (true) {
        
        std::cout << ">>> ";
        std::getline(std::cin, input); //If I do not use getline it will only take the first complete string out of the input, thank you Kira for making me realise that... By giving me code without getline.
        g_cmdcount++;

        if (input == "cls") {
            break;
        }

        else {
            check_cmd(input);
        }
    }
}