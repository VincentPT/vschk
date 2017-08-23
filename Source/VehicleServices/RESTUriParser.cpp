#include "web_common.h"
#include "RESTUriParser.h"
#include "common\string_util.hpp"
#include <list>
#include "common\string_util.hpp"

namespace crab {

	bool inline isParam(const TSTRING& subPath) {
		return subPath[0] == '{' && subPath[subPath.size() - 1] == '}';
	}

	RESTUriParser::RESTUriParser()
	{
	}

	RESTUriParser::~RESTUriParser()
	{
	}

	std::list<TSTRING>& RESTUriParser::getPattern() {
		return _pattern;
	}

	void RESTUriParser::setSignPath(const TSTRING& path) {
		_signPath = path;
	}
	const TSTRING& RESTUriParser::getSignPath() const {
		return _signPath;
	}

	bool RESTUriParser::parseParams(const TSTRING& path, std::vector<TSTRING>& params) {
		std::list<TSTRING> branches;
		makePathSignature(path, &branches);
		return parseParams(branches, &params);
	}

	bool RESTUriParser::parseParams(const std::list<TSTRING>& branches, std::vector<TSTRING>* pparams) {
		if (branches.size() != _pattern.size()) {
			return false;
		}

		auto it1 = _pattern.begin();
		auto it2 = branches.begin();

		if(pparams) pparams->reserve(_pattern.size());

		for (; it1 != _pattern.end(); it1++, it2++) {
			auto& sub_pattern = *it1;
			auto& sub_path = *it2;
			if (isParam(sub_pattern)) {
				if (pparams) {
					if (isParam(sub_path)) {
						pparams->push_back(U(""));
					}
					else {
						pparams->push_back(sub_path);
					}
				}
			}
			else if (sub_path != sub_pattern) {
				if(pparams) pparams->clear();
				return false;
			}
		}

		return true;
	}

	void split(const TSTRING& s, std::list<TSTRING>& sarr) {
		auto pc = s.c_str();
		auto pc_end = pc + s.length();
		auto last = pc;
		while (pc < pc_end) {
			if (*pc == '/') {
				if (pc > last) {
					sarr.push_back(TSTRING(last, pc - last));
				}
				pc++;
				while (pc < pc_end && *pc == '/') {
					pc++;
				}
				last = pc;
			}
			else {
				pc++;
			}
		}

		if (*(pc_end - 1) != '/') {
			sarr.push_back(TSTRING(last, pc_end - last));
		}
	}

	TSTRING RESTUriParser::makePathSignature(const TSTRING& path, std::list<TSTRING>* branches) {
		TSTRING signPath;				
		std::shared_ptr<std::list<TSTRING>> branchesRef;
		
		if (!branches) {
			branchesRef = std::make_shared<std::list<TSTRING>>();
			branches = branchesRef.get();
		}
		auto& sarr = *branches;
		sarr.clear();

		split(path, sarr);
		int paramCount = 0;
		for (auto it = sarr.begin(); it != sarr.end(); it++) {
			auto& substr = *it;
			trim(substr);
			toLower(substr);
			if(isParam(substr)) {
				substr = U("{");
				substr.append(toString(paramCount));
				substr.append(U("}"));
				signPath.append(substr);
				paramCount++;
			}
			else {
				signPath.append(substr);				
			}
			signPath.append(U("/"));
		}
		if (signPath.size()) {
			signPath.erase(signPath.size() - 1);
		}

		return signPath;
	}

	bool CompareParserRef::operator() (const RESTUriParserRef& p1, const RESTUriParserRef& p2) const {
		return p1->getSignPath() < p2->getSignPath();
	}
}
