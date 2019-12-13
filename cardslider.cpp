#include "cardslider.h"

using namespace std;

CardSlider::CardSlider(int _cardWidth, int _cardHeight) :
    cardWidth(_cardWidth), cardHeight(_cardHeight)
{
    world = new b2World(b2Vec2(0.0f, 0.0f));
}

CardSlider::~CardSlider() {
}

void CardSlider::moveCard() {
    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz)
    float32 timeStep = 0.017f;
    int32 velocityIterations = 1;
    int32 positionIterations = 1;

    b2Vec2 cardVelocity = body->GetLinearVelocity();

    if(hasZeroVelocity(cardVelocity.x, cardVelocity.y))
    {
        world->DestroyBody(body);

        emit stopTimer();
        return;
    }

    cardVelocity = body->GetLinearVelocity();

    // Instruct the world to perform a single step of simulation.
    // It is generally best to keep the time step and iterations fixed.
    world->Step(timeStep, velocityIterations, positionIterations);

    // Now print the position and angle of the body.
    b2Vec2 position = body->GetPosition();
    float deckToPosX = position.x - deckX;
    float deckToPosY = position.y - deckY;
    b2Vec2 deckToPosDisplay = b2Vec2(deckX + deckToPosX * SPEED_SCALE_FACTOR,
                                     deckY + deckToPosY * SPEED_SCALE_FACTOR);

    emit sendCardPos(deckToPosDisplay.x, deckToPosDisplay.y);
}

float CardSlider::acceleration(float velocity, float distance)
{
    return -pow(velocity, 2) / 2 / distance;
}

void CardSlider::resetWorld() {
    delete world;
    world = new b2World(b2Vec2(0.0f, 0.0f));
}

bool CardSlider::hasZeroVelocity(float velX, float velY) {
    return signbit(velX) != velXinitialSign || signbit(velY) != velYinitialSign;
}

void CardSlider::setStartingPos(int _startX, int _startY, int _deckX, int _deckY) {
    startX = _startX;
    startY = _startY;
    deckX = _deckX;
    deckY = _deckY;

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(deckX, deckY);
    body = world->CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1, 1);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);
    float distX = (startX - deckX) / SPEED_SCALE_FACTOR;
    float distY = (startY - deckY) / SPEED_SCALE_FACTOR;

    b2Vec2 cardVel = b2Vec2(distX, distY);
    cardVel.Normalize();
    cardVel = b2Vec2(cardVel.x * 100, cardVel.y * 100);

    velXinitialSign = signbit(cardVel.x);
    velYinitialSign = signbit(cardVel.y);
    x = cardVel.x;
    y = cardVel.y;

    float accelX = acceleration(cardVel.x, distX);
    float accelY = acceleration(cardVel.y, distY);

    world->SetGravity(b2Vec2(accelX, accelY));

    body->SetLinearVelocity(cardVel);
}
