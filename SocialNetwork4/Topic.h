#pragma once
#include "Vector.h"
#include "String.h"
#include "Post.h"

class Topic
{
public:

	Topic();

	Topic(const String& title, const String& description,
		const size_t creatorId, const size_t id);

	Topic(const char* title, const char* description,
		const size_t creatorId, const size_t id);

	Topic(const char* title, const char* description,
		const size_t creatorId, const size_t id, const Vector<Post>& posts);

	Topic(const Topic& other);

	~Topic();

	const String& getTitle() const;
	const String& getDescription() const;
	const size_t getCreatorId() const;
	const size_t getId() const;
	Vector<Post>& getPosts();
	const Vector<Post>& getPosts() const;

	void setTitle(const char* newTitle);
	void setTitle(const String& newTitle);

	void setDescription(const char* newDescription);
	void setDescription(const String& newDescription);

	void setCreatorId(const size_t newCreatorId);
	void setId(const size_t newId);
	void addPost(const Post& newPost); // possible move semantics here

	bool isEqualWithoutId(const Topic& other) const;
	bool isNotEqualWithoutId(const Topic& other) const;

	void clear();

	Topic& operator=(const Topic& other);
	bool operator==(const Topic& other) const;
	bool operator!=(const Topic& other) const;

private:
	String title;
	String description;
	size_t creatorId;
	size_t id;
	Vector<Post> posts;

};

