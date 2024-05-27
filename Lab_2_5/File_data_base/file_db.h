#ifndef FILE_DB_H

#define FILE_DB_H

#include<string>
#include<vector>
#include<functional>
#include"Idata_provider.h"
#include<stdexcept>

template<typename TEntity>
struct file_data_base
{
#pragma region Get

	std::vector<TEntity>& GetDataSet()
	{
		return m_file_data_set;
	}
 
#pragma endregion

#pragma region ctor

	file_data_base(Idata_provider<TEntity>* dataProvider, 
		std::function<void(TEntity*, const TEntity&)> edit_proc)
	{		
		m_data_provider = dataProvider;

		m_file_data_set = m_data_provider->ReadFromSource();	

		if (m_edit_proc != nullptr)
			m_edit_proc = edit_proc;
		else
			throw std::runtime_error("Edit procedure not set!");		
	}

#pragma endregion

	void Save()
	{
		m_data_provider->SaveToSource(m_file_data_set);
	}

	virtual bool HasEntity(std::function<bool(const TEntity&)> predicate)
	{
		for (TEntity& e : m_file_data_set)
		{
			if (predicate(e)) return true;
		}

		return false;
	}

	virtual TEntity* Search(std::function<bool(const TEntity&)> predicate)
	{
		for (TEntity& e : m_file_data_set)
		{
			if (predicate(e))
				return &e;
		}

		return nullptr;
	}

	virtual int IndexOf(const TEntity& entity) const
	{
		int res = -1;

		int count = 0;

		for (auto& e : m_file_data_set)
		{
			if (e == entity)
			{
				res = count;
				break;
			}

			++count;
		}
			
		return res;
	}

	virtual void Add(const TEntity& entity)
	{
		m_file_data_set.push_back(entity);
	}

	virtual void AddRange(const std::vector<TEntity>& range)
	{
		for (const TEntity& en : range)
		{
			m_file_data_set.push_back(en);
		}
	}

	virtual void Edit(const TEntity& entity, const TEntity& newEntity)
	{
		TEntity* found_entity = Search([entity](const TEntity& ent)->bool { return ent == entity; });

		if (found_entity != nullptr)
		{
			m_edit_proc(found_entity, newEntity);
		}
		else
		{
			throw std::runtime_error("Entity for editing not found!");
		}
	}

	virtual void Delete(const TEntity& entity)
	{
		int index = IndexOf(entity);

		if (index >= 0)
		{
			m_file_data_set.erase(m_file_data_set.begin() + index);
		}
		else
		{
			throw std::runtime_error("Entity for deleting not found!");
		}
	}

	virtual void DeleteRange(const std::vector<TEntity>& range)
	{
		int index = -1;

		for (const TEntity& ent_for_del : range)
		{
			index = IndexOf(ent_for_del);

			if (index >= 0)
				m_file_data_set.erase(m_file_data_set.begin() + index);
			else
				throw std::runtime_error("Entity for deleting not found!");

			index = -1;
		}
	}
	
	file_data_base(const file_data_base& other) = delete;

	file_data_base& operator = (const file_data_base& other) = delete;

private:

	std::vector<TEntity> m_file_data_set;

	Idata_provider<TEntity>* m_data_provider;

	std::function<void(TEntity*, const TEntity&)> m_edit_proc;
};

#endif // !FILE_DB_H

