#pragma once
#include "String.h"
#include "Vector.h"
#include "Reply.h"
#include "Reaction.h"

class Reply;

class Comment
{
public:

	//constructors and destructor
	Comment();

	Comment(const String& author, const String& text,
		const int score, const size_t id, const size_t postId, const size_t authorId);

	Comment(const char* author, const char* text,
		const int score, const size_t id, const size_t postId, const size_t authorId);

	Comment(const Comment& other);

	~Comment();

	//operators
	Comment& operator=(const Comment& other);
	bool operator==(const Comment& other) const;
	bool operator!=(const Comment& other) const;

	//methods tied to operators
	bool isEqualWithoutId(const Comment& other) const;
	bool isNotEqualWithoutId(const Comment& other) const;

	//getters
	const String& getAuthor() const;
	const String& getText() const;
	const int getScore() const;
	const size_t getId() const;
	const size_t getPostId() const;
	const size_t getAuthorId() const;

	const Vector<Reply>& getReplies() const;
	Vector<Reply>& getReplies();

	const Vector<Reaction>& getReactions() const;
	Vector<Reaction>& getReactions();

	//setters
	void setAuthor(const char* newAuthor);
	void setAuthor(const String& newAuthor);

	void setText(const char* newText);
	void setText(const String& newText);

	void setScore(const int newScore);
	void setId(const size_t newId);
	void setPostId(const size_t newPostId);
	void setAuthorId(const size_t newId);
	void setReplies(const Vector<Reply>& newReplies);
	void setReactions(const Vector<Reaction>& newReactions);

	//methods
	void clear();

	void changeReactionType(const size_t reactionPosition, const ReactionType newReactionType);	

	void incrementScore(const int amount);
	void decrementScore(const int amount);

	const Reaction* getUserReaction(const size_t userId) const;

	void addReply(const Reply& newReply);
	void addReaction(Reaction& newReaction);

private:

	friend class Reply;

	String author;
	String text;
	int score;
	size_t id;
	size_t postId;
	size_t authorId;

	Vector<Reaction> reactions;
	Vector<Reply> replies;
};

