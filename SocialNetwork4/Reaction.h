#pragma once
#include <iostream> // for SIZE_MAX

enum ReactionType {

	downvote = 0,
	upvote = 1,
	undefined = 2,

	ReactionTypeCount
};

class Reaction
{
public:

	Reaction();

	Reaction(const size_t userId, const ReactionType reaction);

	Reaction(const size_t userId, const ReactionType reaction, const size_t position);

	Reaction(const Reaction& other);

	const size_t getUserId() const;
	const ReactionType getReactionType() const;
	const size_t getPosition() const;

	void setUserId(const size_t newUserId);
	void setReaction(const ReactionType newReaction);
	void setPosition(const size_t newPosition);

	Reaction& operator=(const Reaction& other);

	bool operator==(const Reaction& other) const;
	bool operator!=(const Reaction& other) const;

private:
	size_t userId;
	ReactionType reaction;
	size_t position;
};

