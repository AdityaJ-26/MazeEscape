#include <random>

#include "Entity.h"

Entity::Entity(SDL_Renderer* renderer) :
	keyTex(nullptr),
	botTex(nullptr)
{
	keyTex->load(renderer, KEY_PNG_PATH);
	botTex->load(renderer, BOT_PNG_PATH);
}

Entity::~Entity() {
	delete keyTex;
	keyTex = nullptr;
	delete botTex;
	botTex = nullptr;
	for (auto& key : keys) {
		delete key;
		key = nullptr;
	}
	for (auto& bot : bots) {
		delete bot;
		bot = nullptr;
	}
}

const double Entity::distance(const int32_t& x1, const int32_t& y1, const double& x2, const double& y2) const {
	return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}
const double Entity::distance(const Coordinate& c1, const Coordinate& c2) const {
	return sqrt(pow((c1.y - c2.y), 2) + pow((c1.y - c2.y), 2));
}

/* -------------------------------------------------- */
// Spawn
/* -------------------------------------------------- */
void Entity::spawnKeys(Map* map, Player* player) {
	std::default_random_engine engine(int(time(0)));
	std::uniform_int_distribution dist(1, map->maze->size() - 2);

	int32_t count = 0;
	const Coordinate& p = player->character->coord();
	while (count < Constant::MAX_KEYS) {
		int32_t x = dist(engine);
		int32_t y = dist(engine);
		if (map->maze->cellType(y, x) == way &&
			distance(x, y, p.x, p.y) > KEY_SPAWN_DISTANCE)
		{
			keys[count++] = new Key{ x, y };
		}
	}
}

void Entity::spawnBot(Map* map, Player* player) {
	std::default_random_engine engine(static_cast<int>(time(0)));
	std::uniform_int_distribution dist(1, map->maze->size() - 2);

	while (true) {
		int32_t x = dist(engine);
		int32_t y = dist(engine);
		const Coordinate& c = player->character->coord();
		if (map->maze->cellType(y, x) == way &&
			(distance(x, y, c.x, c.y) > MIN_DISTANCE))
		{
			bots.push_back(new Bot(x, y));
			bots.back()->pathFind(*(map->maze), player->character->coord());
			break;
		}
	}
}

void Entity::render(SDL_Renderer* renderer, Camera* camera) const {

	SDL_Rect* rect = new SDL_Rect();
	rect->h = TILE_SIZE;
	rect->w = TILE_SIZE;

	
	for (const auto& key : keys) {
		if (key == nullptr) continue;
		const Coordinate& k = key->coord();
		if (k.x >= camera->start_x && k.y >= camera->start_y && k.x <= camera->end_x && k.y <= camera->end_y) {
			rect->x = static_cast<int> ((k.x - camera->start_x) * TILE_SIZE);
			rect->y = static_cast<int> ((k.y - camera->start_y) * TILE_SIZE);
			SDL_RenderCopy(renderer, keyTex->tex, nullptr, rect);
		}
	}

	for (const auto& bot : bots) {
		const Coordinate& k = bot->coord();
		if (k.x >= camera->start_x && k.y >= camera->start_y && k.x <= camera->end_x && k.y <= camera->end_y) {
			rect->x = static_cast<int> ((k.x - camera->start_x) * TILE_SIZE);
			rect->y = static_cast<int> ((k.y - camera->start_y) * TILE_SIZE);
			SDL_RenderCopy(renderer, botTex->tex, nullptr, rect);
		}
	}
}


void Entity::moveBots(Map* map, const double& deltaTime) {
	for (auto& bot : bots) {
		if (!Physics::move(map->maze, bot, deltaTime)) {
			bot->changeDirection();
		}
	}
}