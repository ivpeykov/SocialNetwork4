#pragma once
#include "Vector.h"
#include "CustomString.h"
#include "Discussion.h"

class Topic
{
public:

	Topic();


	Topic(CustomString& title, CustomString& description,
		unsigned creatorId, unsigned id);

	Topic(const char* title, const char* description,
		unsigned creatorId, unsigned id);

	Topic(const char* title, const char* description,
		unsigned creatorId, unsigned id, Vector<Discussion>& discussions);

	Topic(const Topic& other);


	~Topic();

	const CustomString& getTitle() const;
	const CustomString& getDescription() const;
	const unsigned getCreatorId() const;
	const unsigned getId() const;
	Vector<Discussion>& getDiscussions();

	void setTitle(const char* newTitle);
	void setTitle(CustomString& newTitle);

	void setDescription(const char* newDescription);
	void setDescription(CustomString& newDescription);

	void setCreatorId(unsigned newCreatorId);
	void setId(unsigned newId);
	void addDiscussion(Discussion& newDiscussion);

	bool isEqualWithoutId(const Topic& other) const;
	bool isNotEqualWithoutId(const Topic& other) const;

	Topic& operator=(const Topic& other);
	bool operator==(const Topic& other) const;
	bool operator!=(const Topic& other) const;

private:
	CustomString title;
	CustomString description;
	unsigned creatorId;
	unsigned id;
	Vector<Discussion> discussions;

};

