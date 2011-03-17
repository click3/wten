
namespace wten {

#pragma pack(push, 4)
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
template <typename Iterator, typename result_type>
struct ListCSVParserBase : boost::spirit::qi::grammar<Iterator, std::vector<result_type>()> {
	ListCSVParserBase() :
		ListCSVParserBase::base_type(root)
	{
	}

	void Initialize(const boost::spirit::qi::rule<Iterator, result_type()>& data_line) {
		namespace qi = boost::spirit::qi;
		using boost::spirit::standard_wide::char_;
		using qi::lexeme;

		quoted_string = lexeme['"' >> +(char_ - '"') >> '"'][qi::_val = boost::phoenix::bind(&WStrV2Ptr, qi::_1)];
		unquoted_string = (+(char_ - ',' - '"'))[qi::_val = boost::phoenix::bind(&WStrV2Ptr, qi::_1)];
		string = quoted_string | unquoted_string;
		comment_line = "//" >> *(char_ - '\n') >> -char_('\n');
		empty_line = '\n';
		this->data_line = data_line;
		line = *(comment_line | empty_line) >> this->data_line;
		root = +(line) >> *(comment_line | empty_line);
	}

	boost::spirit::qi::rule<Iterator, boost::shared_ptr<const std::wstring>()> quoted_string;
	boost::spirit::qi::rule<Iterator, boost::shared_ptr<const std::wstring>()> unquoted_string;
	boost::spirit::qi::rule<Iterator, boost::shared_ptr<const std::wstring>()> string;
	boost::spirit::qi::rule<Iterator> comment_line;
	boost::spirit::qi::rule<Iterator> empty_line;
	boost::spirit::qi::rule<Iterator, result_type()> data_line;
	boost::spirit::qi::rule<Iterator, result_type()> line;
	boost::spirit::qi::rule<Iterator, std::vector<result_type>() > root;
};
#pragma warning(pop)
#pragma pack(pop)

} // wten
