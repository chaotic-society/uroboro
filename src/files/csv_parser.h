
///
/// @file csv_parser.h Parser to load numerical data from CSV file
///

#ifndef THEORETICA_CSV_PARSER_H
#define THEORETICA_CSV_PARSER_H

#include <fstream>
#include <string>
#include <map>

#include "../algebra/vec.h"


namespace theoretica {

	/// @namespace theoretica::files Utilities to load data from files.
	namespace files {


		/// Parse a line of text to separate it into a list
		/// of tokens, separated originally by a delimiter
		/// such as a comma.
		inline std::vector<std::string> tokenize_csv(
			const std::string& line,
			const std::string& delimiter = ",") {

			std::vector<std::string> tokens;

			// ...

			return tokens;
		}


		/// Load numerical data from a CSV file with
		/// header information into a table.
		///
		/// @param filename The name of the file
		/// @return A table holding the data as a map of vectors
		inline auto load_csv(
			const std::string& filename,
			const std::string& delimiter = ",") {

			std::ifstream file(filename);
			std::string line;

			// Unable to open file
			if(!file.is_open()) {
				TH_MATH_ERROR("files::load_csv", file.is_open(), IMPOSSIBLE_OPERATION);
				std::map<std::string, vec<real>> err_table;
				err_table["error"] = { nan() };
				return err_table;
			}


			std::vector<std::string> column_names;
			std::vector<std::string> tokens;
			std::vector<std::vector<real>> entries;

			// Read first line and parse it as
			// data or as header
			std::getline(file, line);
			column_names = tokenize_csv(line, delimiter);

			bool is_header = false;

			// Check if tokens are text or numerical data
			for (const auto& token : tokens) {

				// if(!is_numerical(token))
				// 	is_header = true;
			}

			entries.reserve(column_names.size());

			// Add first data row if line is not an header
			if(!is_header) {

				for (int col = 0; col < column_names.size; ++col)
					entries[col].push_back(std::stod(column_names[col]));
			}


			while(std::getline(file, line)) {

				tokens = tokenize_csv(line, delimiter);

				// The length of the row is incoherent
				if(tokens.size() != column_names.size()) {

					TH_MATH_ERROR("files::load_csv", tokens.size(), INVALID_ARGUMENT);
					std::map<std::string, vec<real>> err_table;
					err_table["error"] = { nan() };
					return err_table;
				}

				// Add data entries
				for (const auto& token : tokens) {

					
				}
			}


			std::map<std::string, vec<real>> table;

			// Construct table ...

			return table;
		}

	}

}


#endif
