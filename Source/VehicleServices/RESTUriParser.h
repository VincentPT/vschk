#pragma once
#include <vector>
#include <memory>

namespace crab {
	class RESTUriParser
	{
		std::list<TSTRING> _pattern;
		TSTRING _signPath;
	public:
		RESTUriParser();
		std::list<TSTRING>& getPattern();
		void setSignPath(const TSTRING&);
		const TSTRING& getSignPath() const;
		~RESTUriParser();
		bool parseParams(const TSTRING& path, std::vector<TSTRING>& params);
		bool parseParams(const std::list<TSTRING>& , std::vector<TSTRING>* params = nullptr);
		static TSTRING makePathSignature(const TSTRING& path, std::list<TSTRING>* branches = nullptr);		
	};

	typedef std::shared_ptr<RESTUriParser> RESTUriParserRef;

	struct CompareParserRef
	{
		bool operator() (const RESTUriParserRef& p1, const RESTUriParserRef& p2) const;
	};	
}
