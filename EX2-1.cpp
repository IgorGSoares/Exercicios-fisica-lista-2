#include "test.h"
#include <chrono>
#include <thread>

using namespace std::chrono;
using namespace std::this_thread;

class EX2_1 : public Test //você cria a sua classe derivada da classe base Test
{
public:
	EX2_1() {
		// Aqui no construtor você inicializa a cena

		CreateFloor();

		b2Body* b1;
		{
			// Define the dynamic body. We set its position and call the body factory.
			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody;
			bodyDef.position.Set(0.0f, 2.0f);
			b1 = m_world->CreateBody(&bodyDef);

			// Define another box shape for our dynamic body.
			b2PolygonShape dynamicBox;
			dynamicBox.SetAsBox(0.5f, 2.0f);

			// Define the dynamic body fixture.
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &dynamicBox;

			// Set the box density to be non-zero, so it will be dynamic.
			fixtureDef.density = 1.0f;

			// Override the default friction.
			fixtureDef.friction = 0.5f;

			//bounciness
			fixtureDef.restitution = 0.0f;

			// Add the shape to the body.

			b1->CreateFixture(&fixtureDef);
		}

		b2Body* b2;
		{
			// Define the dynamic body. We set its position and call the body factory.
			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody;
			bodyDef.position.Set(2.0f, 2.0f);
			b2 = m_world->CreateBody(&bodyDef);

			// Define another box shape for our dynamic body.
			b2PolygonShape dynamicBox;
			dynamicBox.SetAsBox(0.5f, 2.0f);

			// Define the dynamic body fixture.
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &dynamicBox;

			// Set the box density to be non-zero, so it will be dynamic.
			fixtureDef.density = 1.0f;

			// Override the default friction.
			fixtureDef.friction = 0.5f;

			//bounciness
			fixtureDef.restitution = 0.0f;

			// Add the shape to the body.

			b2->CreateFixture(&fixtureDef);
		}

		b2Body* b3;
		{
			// Define the dynamic body. We set its position and call the body factory.
			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody;
			bodyDef.position.Set(4.0f, 2.0f);
			b3 = m_world->CreateBody(&bodyDef);

			// Define another box shape for our dynamic body.
			b2PolygonShape dynamicBox;
			dynamicBox.SetAsBox(0.5f, 2.0f);

			// Define the dynamic body fixture.
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &dynamicBox;

			// Set the box density to be non-zero, so it will be dynamic.
			fixtureDef.density = 1.0f;

			// Override the default friction.
			fixtureDef.friction = 0.5f;

			//bounciness
			fixtureDef.restitution = 0.0f;

			// Add the shape to the body.

			b3->CreateFixture(&fixtureDef);
		}

		b2Body* b4;
		{
			// Define the dynamic body. We set its position and call the body factory.
			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody;
			bodyDef.position.Set(6.0f, 2.0f);
			b4 = m_world->CreateBody(&bodyDef);

			// Define another box shape for our dynamic body.
			b2PolygonShape dynamicBox;
			dynamicBox.SetAsBox(0.5f, 2.0f);

			// Define the dynamic body fixture.
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &dynamicBox;

			// Set the box density to be non-zero, so it will be dynamic.
			fixtureDef.density = 1.0f;

			// Override the default friction.
			fixtureDef.friction = 0.5f;

			//bounciness
			fixtureDef.restitution = 0.0f;

			// Add the shape to the body.

			b4->CreateFixture(&fixtureDef);
		}

		b2Body* b5;
		{
			// Define the dynamic body. We set its position and call the body factory.
			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody;
			bodyDef.position.Set(8.0f, 2.0f);
			b5 = m_world->CreateBody(&bodyDef);

			// Define another box shape for our dynamic body.
			b2PolygonShape dynamicBox;
			dynamicBox.SetAsBox(0.5f, 2.0f);

			// Define the dynamic body fixture.
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &dynamicBox;

			// Set the box density to be non-zero, so it will be dynamic.
			fixtureDef.density = 1.0f;

			// Override the default friction.
			fixtureDef.friction = 0.5f;

			//bounciness
			fixtureDef.restitution = 0.0f;

			// Add the shape to the body.

			b5->CreateFixture(&fixtureDef);
		}

		//sleep_for(seconds(10));
		//sleep_until(system_clock::now() + seconds(1));

		/*std::chrono::seconds time(5);
		std::this_thread::sleep_for(time);*/

		b2Vec2 force = b2Vec2(500.0, 0.0);
		//b1->ApplyForceToCenter(force, true);
		b2Vec2 ptG = b1->GetWorldPoint(b2Vec2(-0.5f, 2.0f));
		b1->ApplyForce(force, ptG, true);

	}

	void Step(Settings& settings) override
	{
		//Chama o passo da simulação e o algoritmo de rendering
		Test::Step(settings);

		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Este e' um template para os exercicios!! :)");
		m_textLine += 15;
	}

	static Test* Create()  //a classe Test que instancia um objeto da sua nova classe
						   //o autor da Box2D usa um padrão de projeto chamado Factory
						   //para sua arquitetura de classes
	{
		return new EX2_1;
	}

	void Keyboard(int key) override
	{
		switch (key)
		{
		case GLFW_KEY_B:
			CreateBox(0.0f, 2.0f, 1.0f, 2.0f, 1.0f, 0.3f, 0.0f);
			break;

		case GLFW_KEY_C:
			CreateCircle(-20.0f, 10.0f, 1.5f, 1.0f, 0.3f, 0.5f);
			break;

		/*case GLFW_KEY_F:

			break;*/
		}
	}

	void CreateCircle(float x, float y, float radius,
		float density, float friction, float restitution) //compound shapes
	{
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(x, y);
		b2Body* body = m_world->CreateBody(&bodyDef);

		b2CircleShape circle;
		circle.m_radius = radius;
		//circle.m_p.Set(0.0f, 2.0f); ???

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &circle;

		fixtureDef.density = density;

		fixtureDef.friction = friction;

		fixtureDef.restitution = restitution;

		body->CreateFixture(&fixtureDef);
	}

	void CreateBox(float x, float y, float width, float height,
		float density, float friction, float restitution)
	{
		// Define the dynamic body. We set its position and call the body factory.
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(x, y);
		b2Body* body = m_world->CreateBody(&bodyDef);

		// Define another box shape for our dynamic body.
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(width, height);

		// Define the dynamic body fixture.
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;

		// Set the box density to be non-zero, so it will be dynamic.
		fixtureDef.density = density;

		// Override the default friction.
		fixtureDef.friction = friction;

		//bounciness
		fixtureDef.restitution = restitution;

		// Add the shape to the body.
		body->CreateFixture(&fixtureDef);
	}

	void CreateEdge(float x, float y)//shape editing
	{
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position.Set(x, y);
		b2Body* body = m_world->CreateBody(&bd);

		b2Vec2 vertices[3];

		/*b2PolygonShape left;
		vertices[0].Set(a.x, a.y);
		vertices[1].Set(b, a.x);
		vertices[2].Set(a.y, c);
		left.Set(vertices, 3);*/

		b2PolygonShape left;
		vertices[0].Set(-2.0f, 0.0f);
		vertices[1].Set(1.0f, 2.0f);
		vertices[2].Set(0.0f, 4.0f);
		left.Set(vertices, 3);

		body->CreateFixture(&left, 2.0f);
	}

	void CreateFloor()
	{
		// Define the ground body.
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(0.0f, -10.0f);

		// Call the body factory which allocates memory for the ground body
		// from a pool and creates the ground box shape (also from a pool).
		// The body is also added to the world.
		b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

		// Define the ground box shape.
		b2PolygonShape groundBox;

		// The extents are the half-widths of the box.
		groundBox.SetAsBox(50.0f, 10.0f);

		// Add the ground fixture to the ground body.
		groundBody->CreateFixture(&groundBox, 0.0f);
	}


};

//Aqui fazemos o registro do novo teste 
static int testIndex = RegisterTest("Examples", "EX2_1", EX2_1::Create);