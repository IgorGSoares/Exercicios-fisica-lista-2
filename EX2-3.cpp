#include "test.h"

b2Body* b1;

b2Vec2 force;
b2Vec2 ptG;

int count = 0;

//b2Vec2 force = decomposeVector(angle, intensity);
//body->ApplyForceToCenter(force, true);

class EX2_3 : public Test //você cria a sua classe derivada da classe base Test
{
public:
	EX2_3() {
		// Aqui no construtor você inicializa a cena
		
		b1 = CreateBox(0.0f, 2.0f, 1.0f, 2.0f, 0.5f, 1.0f, 0.5f);
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
		return new EX2_3;
	}

	void Keyboard(int key) override
	{
		switch (key)
		{
		case GLFW_KEY_W:
			if (count < 10)//count<2
			{
				//force = decomposeVector(90.0f, 3000.0f);
				force = decomposeVector(90.0f, 50.0f+count);
				b1->ApplyForceToCenter(force, true);
				b1->ApplyLinearImpulse(force, b1->GetWorldCenter(), true);
				count+=5;//count++
			}
			else
			{
				count = 0;
			}
			break;

		case GLFW_KEY_A:
			//force = b2Vec2(-2000.0, 0.0);
			force = b2Vec2(-30.0, 0.0);
			/*ptG = b1->GetWorldPoint(b2Vec2(-0.5f, 2.0f));
			b1->ApplyForce(force, ptG, true);*/
			b1->ApplyForceToCenter(force, true);
			b1->ApplyLinearImpulse(force, b1->GetWorldCenter(), true);
			break;

		case GLFW_KEY_D:
			//force = b2Vec2(2000.0, 0.0);
			force = b2Vec2(30.0, 0.0);
			/*ptG = b1->GetWorldPoint(b2Vec2(-0.5f, 2.0f));
			b1->ApplyForce(force, ptG, true);*/
			b1->ApplyForceToCenter(force, true);
			b1->ApplyLinearImpulse(force, b1->GetWorldCenter(), true);
			break;
		}
	}

	b2Body* CreateBox(float x, float y, float width, float height,
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

		return body;
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
static int testIndex = RegisterTest("Examples", "EX2_3", EX2_3::Create);