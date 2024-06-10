
///
/// @file data_table.h A data structure holding a table of numerical values
/// where each column has a name.
///

#ifndef THEORETICA_DATA_TABLE_H
#define THEORETICA_DATA_TABLE_H

#include <map>
#include <string>

#include "../core/constants.h"
#include "../algebra/vec.h"


namespace theoretica {

	/// @class data_table
	/// A data structure holding a table of numerical values,
	/// such as experimental datasets, where each column has a name.
	template<typename Type = real>
	class data_table {
	private:

		/// Hashmap holding the columns by column name
		std::map<std::string, vec<Type>> table;

		/// Ordered list of column names
		std::vector<std::string> indicies;

	public:

		/// Default constructor
		data_table() {}


		/// Construct from a list of the names
		/// of the column datasets.
		data_table(std::initializer_list<std::string> l) {

			indicies.reserve(l.size());
			size_t i = 0;

			for (const auto& name : l) {

				table.insert(std::make_pair(name, vec<Type>()));
				
				indicies[i] = name;
				i++;
			}
		}


		/// Get a reference to a column by column index.
		inline vec<Type>& operator[](unsigned int i) {
			return table[indicies[i]];
		}


		/// Get a const reference to a column by column index.
		inline const vec<Type>& operator[](unsigned int i) const {
			return table[indicies[i]];
		}


		/// Get a reference to a column by column name.
		inline vec<Type>& operator[](const std::string& name) {
			return table[name];
		}


		/// Get a const reference to a column by column name.
		inline const vec<Type>& operator[](const std::string& name) const {
			return table[name];
		}


		/// Insert a new column in the last place.
		inline void insert(std::string name, const vec<Type>& v) {

			table[name] = v;

			// Column doesn't exist yet.
			if(table.find(name) == table.end())
				indicies.emplace_back(name);
		}
		
	};

}


#endif
