#pragma once
#include "Vector.h"
#include "String.h"
#include "Comment.h"

class Post
{
public:

	//constructors and destructor
	Post();

	Post(String& title, String& content,
		size_t topicId, size_t creatorId, size_t id);

	Post(const char* title, const char* content,
		size_t topicId, size_t creatorId, size_t id);

	Post(const Post& other);

	~Post();

	//operators
	Post& operator=(const Post& other);
	bool operator==(const Post& other) const;
	bool operator!=(const Post& other) const;

	//methods tied to operators
	bool isEqualWithoutId(const Post& other) const;
	bool isNotEqualWithoutId(const Post& other) const;

	//getters
	const String& getTitle() const;
	const String& getContent() const;
	const size_t getTopicId() const;
	const size_t getCreatorId() const;
	const size_t getId() const;
	Vector<Comment>& getComments();
	const Vector<Comment>& getComments() const;

	//setters
	void setTitle(const char* title);
	void setTitle(const String& title);

	void setContent(const char* content);
	void setContent(const String& content);

	void setTopicId(const size_t topicId);
	void setCreatorId(const size_t creatorId);
	void setId(const size_t id);

	//methods
	void clear();
	void addComment(const Comment& newComment);

private:
	String title;
	String content;
	size_t topicId;
	size_t creatorId;
	size_t id;
	Vector<Comment> comments;
};

