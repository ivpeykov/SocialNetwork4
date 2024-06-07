#include "Reaction.h"

//constructors
Reaction::Reaction() : userId(SIZE_MAX), reaction(undefined), position(SIZE_MAX)
{
}

Reaction::Reaction(const size_t userId, const ReactionType reaction) : userId(userId), reaction(reaction), position(SIZE_MAX)
{
}

Reaction::Reaction(const size_t userId, const ReactionType reaction, const size_t position) : userId(userId), reaction(reaction), position(position)
{
}

Reaction::Reaction(const Reaction& other) : userId(other.userId), reaction(other.reaction), position(other.position)
{
}

//operators
Reaction& Reaction::operator=(const Reaction& other)
{
	if (this != &other) {
		userId = other.userId;
		reaction = other.reaction;
		position = other.position;
	}
	return *this;
}

bool Reaction::operator==(const Reaction& other) const
{
	return (userId == other.userId && reaction == other.reaction && position == other.position);
}

bool Reaction::operator!=(const Reaction& other) const
{
	return !(*this == other);
}

//getters
const size_t Reaction::getUserId() const
{
	return userId;
}

const ReactionType Reaction::getReactionType() const
{
	return reaction;
}

const size_t Reaction::getPosition() const
{
	return position;
}

//setters
void Reaction::setUserId(const size_t newUserId)
{
	userId = newUserId;
}

void Reaction::setReaction(const ReactionType newReaction)
{
	reaction = newReaction;
}

void Reaction::setPosition(const size_t newPosition)
{
	position = newPosition;
}