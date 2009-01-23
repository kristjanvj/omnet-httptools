
// ***************************************************************************
// 
// HttpTools Project
//// This file is a part of the HttpTools project. The project was created at
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

#ifndef __httptLogdefs_H_
#define __httptLogdefs_H_

#define LL_NONE 0 
#define LL_INFO 1
#define LL_DEBUG 2

#define EV_DEBUG (ev.disabled()||ll<LL_DEBUG) ? (std::ostream&)ev : ev << fullPath() << " #DEBUG#    : "
#define EV_INFO (ev.disabled()||ll<LL_INFO) ? (std::ostream&)ev : ev << fullPath() << " #INFO#     : "
#define EV_WARNING ev.disabled() ? (std::ostream&)ev : ev << fullPath() << " #WARNING#  : "
#define EV_ERROR ev.disabled() ? (std::ostream&)ev : ev << fullPath() << " #ERROR#    : "
#define EV_SUMMARY (ev.disabled()||ll<LL_INFO) ? (std::ostream&)ev : ev << fullPath() << " #SUMMARY#    : "

#endif /* __httptLogdefs_H_ */
