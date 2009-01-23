
// ***************************************************************************
// 
// HttpTools Project
//// This file is a part of the HttpTools project. The project was created at
// Reykjavik University, the Laboratory for Dependable Secure Systems (LDSS).
// Its purpose is to create a set of OMNeT++ components to simulate browsing
// behaviour in a high-fidelity manner along with a highly configurable 
// Web server component.
//
// Maintainer: Kristjan V. Jonsson (LDSS) kristjanvj04@ru.is
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
 
#ifndef __httptRandom_H_
#define __httptRandom_H_

#include <exception>
#include <string>
#include <omnetpp.h>

enum DISTR_TYPE {dt_normal, dt_uniform, dt_exponential, dt_histogram, dt_constant,dt_zipf};

#define DISTR_NORMAL_STR "normal"
#define DISTR_UNIFORM_STR "uniform"
#define DISTR_EXPONENTIAL_STR "exponential"
#define DISTR_HISTOGRAM_STR "histogram"
#define DISTR_CONSTANT_STR "constant"
#define DISTR_ZIPF_STR "zipf"

using namespace std;

class rdObject
{
	protected:
		DISTR_TYPE m_type;
	public:
		virtual double get()=0;
	public:
		DISTR_TYPE type() {return m_type;}
		string typeStr();
		virtual string toString() {return typeStr();}
	protected:
		bool _hasKey(cXMLAttributeMap attributes,string key) {return attributes.find(key)!=attributes.end();}
};

class rdNormal : public rdObject
{
	protected:
		double m_mean;
		double m_sd;
		double m_min;
		bool m_bMinLimit;
		bool m_nonNegative;
	public:
		rdNormal(double mean, double sd, bool nonNegative=false);
		rdNormal(cXMLAttributeMap attributes);
		void setMinLimit(double min) {m_min=min; m_bMinLimit=true;}
		void resetMinLimit() {m_bMinLimit=false;}
		virtual double get();
};

class rdUniform : public rdObject
{
	protected:
		double m_beginning;
		double m_end;
	public:
		rdUniform(double beginning, double end);
		rdUniform(cXMLAttributeMap attributes);
		virtual double get();
		double getBeginning() {return m_beginning;}
		void setBeginning(double beginning) {m_beginning=beginning;}
		double getEnd() {return m_end;}
		void setEnd(double end) {m_end=end;}
};

class rdExponential : public rdObject
{
	protected:
		double m_mean;
		double m_min;
		double m_max;
		bool m_bMinLimit;
		bool m_bMaxLimit;
	public:
		rdExponential(double mean);
		rdExponential(cXMLAttributeMap attributes);
		virtual double get();
		void setMinLimit(double min) {m_min=min; m_bMinLimit=true;}
		void resetMinLimit() {m_bMinLimit=false;}
		void setMaxLimit(double max) {m_max=max; m_bMaxLimit=true;}
		void resetMaxLimit() {m_bMaxLimit=false;}
};

// TODO: IMPLEMENT!
class rdHistogram : public rdObject
{
	protected:
		cDoubleHistogram m_histogram;
	public:
		rdHistogram(cXMLAttributeMap attributes);
		double get();
};

class rdConstant : public rdObject
{
	protected:
		double m_value;
	public:
		rdConstant(double value);
		rdConstant(cXMLAttributeMap attributes);
		double get();
};

class rdZipf : public rdObject
{
	protected:
		double m_alpha;
		int m_number;
		double m_c;
		bool m_baseZero;
	public:
		rdZipf(cXMLAttributeMap attributes);
		rdZipf(int n,double alpha,bool baseZero=false);
	public:
		virtual double get();
		void setn(int n) {m_number=n;__setup_c();}
		int getn() {return m_number;}
		void setalpha(double alpha) {m_alpha=alpha;__setup_c();}
		double getalpha() {return m_alpha;}
		virtual string toString();
	private:
		void __initialize(int n,double alpha, bool baseZero);
		void __setup_c();
};

class rdObjectFactory
{
	public: 
		rdObject* create( cXMLAttributeMap attributes );	
};

#endif /* __httptRandom_H_ */
