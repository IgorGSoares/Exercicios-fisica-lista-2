#include "test.h"

float angle = 45.0f;
float intensity = 500.0f;

class EX2_2 : public Test //você cria a sua classe derivada da classe base Test
{
public:
	EX2_2() {
		// Aqui no construtor você inicializa a cena

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

		CreateFloor();

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
		return new EX2_2;
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

	void CreateBox(float x, float y, float width, float height,
		float density, float friction, float restitution, float angulo, float intensity)
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

		//b2Vec2 force = b2Vec2(forceX, forceY);
		b2Vec2 force = decomposeVector(angle, intensity);
		body->ApplyForceToCenter(force, true);
	}

	void Keyboard(int key) override
	{
		switch (key)
		{
		case GLFW_KEY_KP_ADD:
			angle += 15.0f;
			break;

		case GLFW_KEY_KP_SUBTRACT:
			angle -= 15.0f;
			break;

		case GLFW_KEY_B:
			CreateBox(-20.0f, 15.0f, 0.5f, 0.5f, 0.5f, 0.3f, 0.0f, angle, intensity);
			break;

		case GLFW_KEY_M:
			intensity += 500;
			break;

		case GLFW_KEY_N:
			intensity -= 500;
			break;
		}
	}

	b2Vec2 decomposeVector(float a, float m)
	{
		b2Vec2 dec;
		dec.x = m * cos(degToRadian(a));
		dec.y = m * sin(degToRadian(a));
		return dec;
	}

	float degToRadian(float a)
	{
		return a * b2_pi / 180.0f;
	}
};

//Aqui fazemos o registro do novo teste 
static int testIndex = RegisterTest("Examples", "EX2_2", EX2_2::Create);