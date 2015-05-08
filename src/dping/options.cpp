//------------------------------------------------------
#include "stdafx.h"
#include "options.h"

#include "common\version.h"			// for VERSION_PRODUCT_NAME, FILE_INTERNAL_NAME, MAIN_PRODUCT_VERSION_STR_A

#include <iostream>

#include <sstream>
#define OSSFMT(expr)	(static_cast<std::ostringstream&>(std::ostringstream() << expr).str())

using namespace std;

//------------------------------------------------------

ProgramOptions::ProgramOptions()
	: bVerbose(false)
	, nMaxTimeoutMs(5000)
	, nPingCount(4)
	, mode(MODE_UNKNOWN)
{

}

//------------------------------------------------------

string GetPrintVersion()
{
	return OSSFMT(VERSION_PRODUCT_NAME ": " FILE_INTERNAL_NAME " v." MAIN_PRODUCT_VERSION_STR_A << endl);
}

//------------------------------------------------------

string GetPrintHelpSuggest()
{
	return OSSFMT("Use \"--help\" command line argument to get help!" << endl);
}

//------------------------------------------------------

string GetPrintHelp()
{
	const char* pszHelpInfo = R"zzz(
Usage: dping [--help]
             [--version]
             [--country code|--asn id] [-n count] [-w timeout] [-v] {target_name}
             --list-country [-v]
             --list-asn code [-v]

Options:
    {target_name}  Destination host IP or domain name.

    --help          Display this help.
    --version       Display program version.
    --country code  Ping from specified 2 letter country code (ISO 3166-1 alpha-2).
                    Pinging by current country is a default setting.
    --asn id        Ping from specified ASN (autonomous system number) network.
    -n count        Number of echo requests to send.
    -w timeout      Timeout in milliseconds to wait for each reply.
    --list-country  List countries available.
    --list-asn code List ASNs for specified 2 letter country code.
    -v              Verbose output

)zzz";
	return pszHelpInfo;
}

//------------------------------------------------------

void CheckArgumentParameterNotEmpty(const string& sArg, const string& sParam)
{
	if (sParam.empty())
	{
		throw exception(OSSFMT("Empty value is not allowed for command line argument \"" << sArg << "\".").c_str());
	}
}

//------------------------------------------------------

int ProgramOptions::ProcessCommandLine(const int argc, const char* const argv[])	// returns non-zero result if process exit required
{
	try
	{
		if (argc <= 1)
		{
			cerr << GetPrintVersion();
			throw exception("The syntax of the command is incorrect.");
		}

		bool bTargetSet = false;

		for (int i = 1; i < argc; ++i)
		{
			const string sArg = argv[i];
			const bool bFirstArg = (1 == i);
			const bool bLastArg = (i + 1 == argc);

			if (bFirstArg && sArg == "--help")
			{
				cout << GetPrintVersion();
				cout << GetPrintHelp();
				return 100;
			}
			if (bFirstArg && sArg == "--version")
			{
				cout << GetPrintVersion();
				return 100;
			}

			if (sArg == "-v")
			{
				bVerbose = true;
			}
			else if (sArg == "-n" && !bLastArg)
			{
				const string sNextArg = argv[++i];
				CheckArgumentParameterNotEmpty(sArg, sNextArg);
				nPingCount = stoul(sNextArg);
			}
			else if (sArg == "-w" && !bLastArg)
			{
				const string sNextArg = argv[++i];
				CheckArgumentParameterNotEmpty(sArg, sNextArg);
				nMaxTimeoutMs = stoul(sNextArg);
			}
			else if (sArg == "--country" && !bLastArg)
			{
				const string sNextArg = argv[++i];
				CheckArgumentParameterNotEmpty(sArg, sNextArg);
				mode = MODE_PING_BY_COUNTRY;
				sModeArgument = sNextArg;
			}
			else if (sArg == "--asn" && !bLastArg)
			{
				const string sNextArg = argv[++i];
				CheckArgumentParameterNotEmpty(sArg, sNextArg);
				mode = MODE_PING_BY_ASN;
				sModeArgument = sNextArg;
			}
			else if (sArg == "--list-country")
			{
				mode = MODE_GET_COUNTRIES;
				sModeArgument.clear();
			}
			else if (sArg == "--list-asn" && !bLastArg)
			{
				const string sNextArg = argv[++i];
				CheckArgumentParameterNotEmpty(sArg, sNextArg);
				mode = MODE_GET_ASNS;
				sModeArgument = sNextArg;
			}
			else if ((MODE_UNKNOWN == mode || MODE_PING_BY_COUNTRY == mode || MODE_PING_BY_ASN == mode) && bLastArg)
			{
				CheckArgumentParameterNotEmpty("{target}", sArg);
				sTarget = sArg;
				bTargetSet = true;
			}
			else
			{
				throw exception(OSSFMT("Unknown command line argument \"" << sArg << "\" or command line is missing required parameter.").c_str());
			}
		}

		if (MODE_UNKNOWN == mode)
		{
			mode = MODE_PING_BY_COUNTRY;
			sModeArgument = "<own>";
		}

		if ((MODE_PING_BY_COUNTRY == mode || MODE_PING_BY_ASN == mode) && !bTargetSet)
		{
			throw exception("Ping target is not specified!");
		}
	}
	catch (exception& e)
	{
		cerr << "ERROR! " << e.what() << endl;
		cerr << GetPrintHelpSuggest();
		return 1;
	}

	//bVerbose = true;

	return 0;
}

//------------------------------------------------------
