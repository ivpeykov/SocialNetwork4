#pragma once
#include "Vector.h"
#include "CustomString.h"
#include "Comment.h"

//add move semantics

class Discussion
{
public:

	Discussion();

	Discussion(CustomString& title, CustomString& content,
		size_t topicId, size_t creatorId, size_t id);

	Discussion(const char* title, const char* content,
		size_t topicId, size_t creatorId, size_t id);

	Discussion(const Discussion& other);

	~Discussion();


	const CustomString& getTitle() const;
	const CustomString& getContent() const;
	const size_t getTopicId() const;
	const size_t getCreatorId() const;
	const size_t getId() const;
	Vector<Comment>& getComments();
	const Vector<Comment>& getComments() const;

	void setTitle(const char* title);
	void setTitle(const CustomString& title);

	void setContent(const char* content);
	void setContent(const CustomString& content);

	void setTopicId(const size_t topicId);
	void setCreatorId(const size_t creatorId);
	void setId(const size_t id);
	void addComment(const Comment& newComment);

	bool isEqualWithoutId(const Discussion& other) const;
	bool isNotEqualWithoutId(const Discussion& other) const;

	Discussion& operator=(const Discussion& other);
	bool operator==(const Discussion& other) const;
	bool operator!=(const Discussion& other) const;

private:
	CustomString title;
	CustomString content;
	size_t topicId;
	size_t creatorId;
	size_t id;
	Vector<Comment> comments;

};