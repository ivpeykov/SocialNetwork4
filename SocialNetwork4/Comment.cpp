#include "Comment.h"

//constructors and destructor
Comment::Comment() : author(nullptr), text(nullptr), score(0), id(SIZE_MAX), 
postId(SIZE_MAX), authorId(SIZE_MAX), replies(1), reactions(0) {
    replies.back().setParentCommentId(id);
}

Comment::Comment(const String& author, const String& text,
    const int score, const size_t id, const size_t postId, const size_t authorId) :
    author(author), text(text), score(score), id(id), postId(postId), authorId(authorId), replies(1), reactions(0) {

    replies.back().setParentCommentId(id);
}

Comment::Comment(const char* author, const char* text,
    const int score, const size_t id, const size_t postId, const size_t authorId) :
    author(author), text(text), score(score), id(id), postId(postId), authorId(authorId), replies(1), reactions(0) {
    replies.back().setParentCommentId(id);
}

Comment::Comment(const Comment& other) : author(other.author), text(other.text), score(other.score), id(other.id), postId(other.postId), authorId(other.authorId), replies(other.replies), reactions(other.reactions)
{
}

Comment::~Comment()
{
}

//operators
Comment& Comment::operator=(const Comment& other)
{
    if (this != &other) {

        author = other.author;
        text = other.text;
        score = other.score;
        id = other.id;
        postId = other.postId;
        authorId = other.authorId;
        replies = other.replies;
        reactions = other.reactions;
    }
    return *this;
}

bool Comment::operator==(const Comment& other) const
{
    return (id == other.id && isEqualWithoutId(other));
}

bool Comment::operator!=(const Comment& other) const
{
    return !(*this == other);
}

//methods tied to operators
bool Comment::isEqualWithoutId(const Comment& other) const
{
    return (author == other.author &&
        text == other.text &&
        score == other.score &&
        postId == other.postId &&
        authorId == other.authorId &&
        replies == other.replies &&
        reactions == other.reactions);
}

bool Comment::isNotEqualWithoutId(const Comment& other) const
{
    return !isEqualWithoutId(other);
}

const String& Comment::getAuthor() const
{
    return author;
}

const String& Comment::getText() const
{
    return text;
}

const int Comment::getScore() const
{
    return score;
}

const size_t Comment::getId() const
{
    return id;
}

const size_t Comment::getPostId() const
{
    return postId;
}

const size_t Comment::getAuthorId() const
{
    return authorId;
}

const Vector<Reply>& Comment::getReplies() const
{
    return replies;
}

Vector<Reply>& Comment::getReplies()
{
    return replies;
}

const Vector<Reaction>& Comment::getReactions() const
{
    return reactions;
}

Vector<Reaction>& Comment::getReactions()
{
    return reactions;
}

//setters
void Comment::setAuthor(const char* newAuthor)
{
    author = newAuthor;
}

void Comment::setAuthor(const String& newAuthor)
{
    author = newAuthor;
}

void Comment::setText(const char* newText)
{
    text = newText;
}

void Comment::setText(const String& newText)
{
    text = newText;
}

void Comment::setScore(const int newScore)
{
    score = newScore;
}

void Comment::setId(const size_t newId)
{
    id = newId;
}

void Comment::setPostId(const size_t newPostId)
{
    postId = newPostId;
}

void Comment::setAuthorId(const size_t newId)
{
    authorId = newId;
}

void Comment::setReplies(const Vector<Reply>& newReplies)
{
    replies = newReplies;
}

void Comment::setReactions(const Vector<Reaction>& newReactions)
{
    reactions = newReactions;
}

//methods
void Comment::clear()
{
    author.clearString();
    text.clearString();
    score = 0;
    id = SIZE_MAX;
    postId = SIZE_MAX;
    authorId = SIZE_MAX;

    replies.clear();
    reactions.clear();
}

void Comment::changeReactionType(const size_t reactionPosition, const ReactionType newReactionType)
{
    if (reactionPosition >= reactions.getSize()) {
        throw std::invalid_argument("Index out of bounds");
    }

    reactions[reactionPosition].setReaction(newReactionType);
}

void Comment::incrementScore(const int amount)
{
    score += amount;
}

void Comment::decrementScore(const int amount)
{
    score -= amount;
}

const Reaction* Comment::getUserReaction(const size_t userId) const
{
    size_t reactionsSize = reactions.getSize();
    for (int i = 0; i < reactionsSize; ++i) {
        if (userId == reactions[i].getUserId()) {
            return &reactions[i];
        }
    }

    return nullptr;
}


void Comment::addReply(const Reply& newReply)
{
    replies.pushBack(newReply);
}

void Comment::addReaction(Reaction& newReaction)
{
    newReaction.setPosition(reactions.getSize());
    reactions.pushBack(newReaction);
}