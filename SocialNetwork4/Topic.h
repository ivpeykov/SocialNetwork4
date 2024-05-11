#pragma once
#include "Vector.h"
#include "CustomString.h"
#include "Discussion.h"

class Topic
{
public:

	Topic();

	Topic(const CustomString& title, const CustomString& description,
		const size_t creatorId, const size_t id);

	Topic(const char* title, const char* description,
		const size_t creatorId, const size_t id);

	Topic(const char* title, const char* description,
		const size_t creatorId, const size_t id, const Vector<Discussion>& discussions);

	Topic(const Topic& other);

	~Topic();

	const CustomString& getTitle() const;
	const CustomString& getDescription() const;
	const size_t getCreatorId() const;
	const size_t getId() const;
	Vector<Discussion>& getDiscussions();
	const Vector<Discussion>& getDiscussions() const;

	void setTitle(const char* newTitle);
	void setTitle(const CustomString& newTitle);

	void setDescription(const char* newDescription);
	void setDescription(const CustomString& newDescription);

	void setCreatorId(const size_t newCreatorId);
	void setId(const size_t newId);
	void addDiscussion(const Discussion& newDiscussion); // possible move semantics here

	bool isEqualWithoutId(const Topic& other) const;
	bool isNotEqualWithoutId(const Topic& other) const;

	Topic& operator=(const Topic& other);
	bool operator==(const Topic& other) const;
	bool operator!=(const Topic& other) const;

private:
	CustomString title;
	CustomString description;
	size_t creatorId;
	size_t id;
	Vector<Discussion> discussions;

};

