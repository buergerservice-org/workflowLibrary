// workflowClient.cpp : Test of workflowLibrary
// Copyright (C) 2021 buergerservice.org e.V. <KeePerso@buergerservice.org>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

#include <windows.h>
#include <iostream>

//for workflowLibrary.lib - copy the newest lib to workflowClient-directory
#include "workflowLibrary.h"
#include <AtlBase.h>
#include <atlconv.h>



std::wstring strtowstr(std::string s)
{
    std::basic_string<TCHAR> textstr;
    CA2W ca2w(s.c_str(), CP_UTF8);
    textstr= ca2w;
    return textstr;
}


int main(int argc, char** argv)
{
    std::string PINstring = "";
    std::string outputstring = "";
    std::basic_string<TCHAR> textstr;
    std::locale::global(std::locale("German_germany.UTF-8"));

    //instantiate a new workflowclass
    workflowLibrary::workflow wf;

    /*
    // generate password --------------------------------------
    srand(time(NULL));
    std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string number = "0123456789";
    std::string specialchar = "_!?+-$%&";
    int random = 0;
    std::string password = "";
    for (int i = 0; i < 5; i++)
    {
        random = rand() % alphabet.size();
        password.append(alphabet, random, 1);
    }
    random = rand() % specialchar.size();
    password.append(specialchar, random, 1);
    random = rand() % number.size();
    password.append(number, random, 1);
    std::cout << "random password is: " << password << std::endl;



    std::string inputstr = password;
    // test openssl -------------------------------------------


    //------------------------
    
    // * Set up the key and iv. Do I need to say to not hard code these in a
    // * real application? :-)
    //

    // A 256 bit key
    unsigned char* key = (unsigned char*)"01234567890123456789012345678901";
    
    // A 128 bit IV 
    unsigned char* iv = (unsigned char*)"0123456789012345";

    // Message to be encrypted
    //unsigned char* input = (unsigned char*)"The quick brown fox jumps over the lazy dog";
    unsigned char* input=(unsigned char*) malloc(sizeof(unsigned char) * inputstr.size());
    memcpy((char*)input, inputstr.c_str(), inputstr.size());
    //
    // Buffer for ciphertext. Ensure the buffer is long enough for the
    // ciphertext which may be longer than the plaintext, depending on the
    // algorithm and mode.
    //
    unsigned char ciphertext[128];

    // Buffer for the decrypted text
    unsigned char decryptedtext[128];

    int decryptedtext_len, ciphertext_len;

    // Encrypt the plaintext
    ciphertext_len = wf.encrypt(input, strlen((char*)input), key, iv,
        ciphertext);

    // Do something useful with the ciphertext here
    printf("Ciphertext is:\n");
    //BIO_dump_fp(stdout, (const char*)ciphertext, ciphertext_len);
    std::string s(reinterpret_cast<char const*>(ciphertext));

    // Decrypt the ciphertext
    decryptedtext_len = wf.decrypt(ciphertext, ciphertext_len, key, iv,
        decryptedtext);

    // Add a NULL terminator. We are expecting printable text
    decryptedtext[decryptedtext_len] = '\0';

    // Show the decrypted text
    printf("Decrypted text is:\n");
    printf("%s\n", decryptedtext);


    return EXIT_FAILURE;
    */

 

    std::cout << "\nBuergerservice.org e.V. workflowClient.exe test of workflowLibrary.\n\n" << std::endl;
    // Check command line arguments.
    if (argc != 2)
    {
        std::cerr <<
            "Usage: workflowClient.exe <PIN>\n" <<
            "Example:\n" <<
            "workflowClient.exe 123456\n";
        return EXIT_FAILURE;
    }
    PINstring = argv[1];
    std::cout << "PIN= " << PINstring << std::endl;

    std::cout << "---------------------------------------" << std::endl;
    //if you like test if keypad is true
    std::cout << "starting getkeypad." << std::endl;
    outputstring = wf.getkeypad();
    std::cout << "keypad= " << outputstring << std::endl;
    std::cout << "---------------------------------------" << std::endl;


    std::cout << "starting getcertificate." << std::endl;
    wf.getcertificate();
    std::wcout << "parsed certificate as StyledString: " << strtowstr(wf.certificateStyledString) << std::endl;
    // certificate description
    std::wcout << "issuerName: " << strtowstr(wf.issuerName) << std::endl;
    std::wcout << "issuerUrl: " << strtowstr(wf.issuerUrl) << std::endl;
    std::wcout << "purpose: " << strtowstr(wf.purpose) << std::endl;
    std::wcout << "subjectName: " << strtowstr(wf.subjectName) << std::endl;
    std::wcout << "subjectUrl: " << strtowstr(wf.subjectUrl) << std::endl;
    CA2W ca2w(wf.termsOfUsage.c_str(), CP_UTF8);
    textstr = ca2w;
    std::wcout << "termsOfUsage: " << textstr << std::endl;
    //std::wcout << "termsOfUsage: " << strtowstr(wf.termsOfUsage) << std::endl;
    std::wcout << "effectiveDate: " << strtowstr(wf.effectiveDate) << std::endl;
    std::wcout << "expirationDate: " << strtowstr(wf.expirationDate) << std::endl;


    std::cout << "---------------------------------------" << std::endl;
    Sleep(3000);
    std::cout << "starting startworkflow." << std::endl;
    //start the workflow of the new workflowclass and show output
    outputstring = wf.startworkflow(PINstring);

    if (outputstring == "e1")
    {
        std::cout << "ERROR - please check AusweisApp2, cardreaderand Personalausweis!Exiting Plugin." << std::endl;
        return EXIT_FAILURE;
    }
    else if (outputstring == "e2")
    {
        std::cout << "ERROR - please check your Personalausweis! Exiting Plugin." << std::endl;
        return EXIT_FAILURE;
    }
    else if (outputstring == "e3")
    {
        std::cout << "ERROR - please check your cardreader! Exiting Plugin." << std::endl;
        return EXIT_FAILURE;
    }
    else if (outputstring == "e4")
    {
        std::cout << "ERROR - AusweisApp2-version less than 1.22.* please update! Exiting Plugin." << std::endl;
        return EXIT_FAILURE;
    }
    else if (outputstring == "e5")
    {
        std::cout << "Warning - retryCounter of Perso <3, please start a selfauthentication direct with AusweisApp2! Exiting Plugin." << std::endl;
        return EXIT_FAILURE;
    }
    else if (outputstring == "e7")
    {
        std::cout << "ERROR - no cardreader found! Exiting Plugin." << std::endl;
        return EXIT_FAILURE;
    }


    std::cout << "---------------------------------------" << std::endl;
    //read the output of the parsed jsondata
    std::wcout << "parsed jsonresult as StyledString: \n" << strtowstr(wf.personalStyledString)<< std::endl;
    std::cout << "---------------------------------------" << std::endl;
    //read the values of single datanames
    std::wcout << "AcademicTitle: " << strtowstr(wf.AcademicTitle) << std::endl;
    std::wcout << "ArtisticName: " << strtowstr(wf.ArtisticName) << std::endl;
    std::wcout << "BirthName: " << strtowstr(wf.BirthName) << std::endl;
    std::wcout << "DateOfBirth: " << strtowstr(wf.DateOfBirth) << std::endl;
    std::wcout << "DocumentType: " << strtowstr(wf.DocumentType) << std::endl;
    std::wcout << "FamilyNames: " << strtowstr(wf.FamilyNames) << std::endl;
    std::wcout << "GivenNames: " << strtowstr(wf.GivenNames) << std::endl;
    std::wcout << "IssuingState: " << strtowstr(wf.IssuingState) << std::endl;
    std::wcout << "Nationality: " << strtowstr(wf.Nationality) << std::endl;
    //personaldata PlaceOfBirth
    std::wcout << "PlaceOfBirth: " << strtowstr(wf.PlaceOfBirth) << std::endl;
    //personaldata PlaceOfResidence
    std::wcout << "City: " << strtowstr(wf.City) << std::endl;
    std::wcout << "Country: " << strtowstr(wf.Country) << std::endl;
    std::wcout << "Street: " << strtowstr(wf.Street) << std::endl;
    std::wcout << "ZipCode: " << strtowstr(wf.ZipCode) << std::endl;
    std::cout << "---------------------------------------\n" << std::endl;
    std::wcout << "keyhash of workflow: \n" << strtowstr(outputstring) << "\n\n" << std::endl;
    std::cout << "---------------------------------------" << std::endl;


}
