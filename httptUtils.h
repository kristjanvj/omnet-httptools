
// ***************************************************************************
// 
// HttpTools Project
//
// Reykjavik University, the Laboratory for Dependable Secure Systems (LDSS).
// Its purpose is to create a set of OMNeT++ components to simulate browsing
// behaviour in a high-fidelity manner along with a highly configurable 
// Web server component.
//
// Maintainer: Kristjan V. Jonsson LDSS kristjanvj04@ru.is
//
// ***************************************************************************
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License version 3
// as published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
// ***************************************************************************

#ifndef __httpUtils_H_
#define __httpUtils_H_

#include <vector>
#include <string>

enum CONTENT_TYPE_ENUM {rt_unknown,rt_html_page,rt_image,rt_text};

using namespace std;

string trimLeft( string str );
string trimRight( string str );
string trimLeft( string str, string delim );
string trimRight( string str, string delim );
string trim( string str );
string extractServerName( const char *path );
string extractResourceName( const char *path );
std::string getDelimited(string str, string ldelim, string rdelim="");
std::vector<std::string> parseResourceName(string resource);
CONTENT_TYPE_ENUM getResourceCategory(vector<std::string> res);
CONTENT_TYPE_ENUM getResourceCategory(string resourceExt);
string htmlErrFromCode(int code);
double safeatof(const char* strval, double defaultVal=0.0);
int safeatoi(const char* strval, int defaultVal=0);
int safeatobool(const char* strval, bool defaultVal=false);

#endif /* __httpUtils_H_ */