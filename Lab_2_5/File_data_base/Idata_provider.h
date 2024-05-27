#include"pch.h"
#ifndef DATA_LOADER_H

#define DATA_LOADER_H

#include<vector>
#include<string>

template<typename TEntity> 
struct Idata_provider
{
	virtual std::vector<TEntity> ReadFromSource() = 0;

	virtual void SaveToSource(const std::vector<TEntity>& data_set ) const = 0;
};

#endif // !DATA_LOADER_H

