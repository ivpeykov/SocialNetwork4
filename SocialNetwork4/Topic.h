#pragma once
#include "Vector.h"
#include "String.h"
#include "Post.h"

class Topic
{
public:

	//constructors and destructor
	Topic();

	Topic(const String& title, const String& description,
		const size_t creatorId, const size_t id);

	Topic(const char* title, const char* description,
		const size_t creatorId, const size_t id);

	Topic(const char* title, const char* description,
		const size_t creatorId, const size_t id, const Vector<Post>& posts);

	Topic(const Topic& other);

	~Topic();

	//operators
	Topic& operator=(const Topic& other);
	bool operator==(const Topic& other) const;
	bool operator!=(const Topic& other) const;

	//methods tied to operators
	bool isEqualWithoutId(const Topic& other) const;
	bool isNotEqualWithoutId(const Topic& other) const;

	//getters
	const String& getTitle() const;
	const String& getDescription() const;
	const size_t getCreatorId() const;
	const size_t getId() const;
	Vector<Post>& getPosts();
	const Vector<Post>& getPosts() const;

	//setters
	void setTitle(const char* newTitle);
	void setTitle(const String& newTitle);

	void setDescription(const char* newDescription);
	void setDescription(const String& newDescription);

	void setCreatorId(const size_t newCreatorId);
	void setId(const size_t newId);

	//methods
	void clear();
	void addPost(const Post& newPost);

private:
	String title;
	String description;
	size_t creatorId;
	size_t id;
	Vector<Post> posts;
};

