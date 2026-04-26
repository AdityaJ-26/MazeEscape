#include <random>

#include "Entity.h"


/* -------------------------------------------------- */
// constructor / destructor
/* -------------------------------------------------- */
Entity::Entity(SDL_Renderer* renderer) :
	keySprite(new Sprite()),
	botSprite(new Sprite())
{
	keySprite->load(renderer, KEY_SPRITE_PATH);
	botSprite->load(renderer, BOT_SPRITE_PATH);
}

Entity::~Entity() {
	delete keySprite;
	keySprite = nullptr;
	delete botSprite;
	botSprite = nullptr;
	for (auto& key : keys) {
		delete key;
		key = nullptr;
	}
	for (auto& bot : bots) {
		delete bot;
		bot = nullptr;
	}
}


/* -------------------------------------------------- */
// distance calculations
/* -------------------------------------------------- */
const float Entity::distance(const int& x1, const int& y1, const float& x2, const float& y2) const {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
const float Entity::distance(const Coordinate& c1, const Coordinate& c2) const {
	return sqrt((c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y));
}


/* -------------------------------------------------- */
// spawning
/* -------------------------------------------------- */
void Entity::spawnKeys(Map* map, Player* player) {
	std::default_random_engine engine(int(time(0)));
	std::uniform_int_distribution dist(1, map->maze->size() - 2);

	int count = 0;
	const Coordinate& p = player->character->coord();
	while (count < Constant::MAX_KEYS) {
		int x = dist(engine);
		int y = dist(engine);

		float cx = (x * Constant::SIZE) + Constant::SIZE / 2;
		float cy = (y * Constant::SIZE) + Constant::SIZE / 2;
		if (map->maze->cellType(y, x) == way &&
			distance(cx, cy, p.x, p.y) > KEY_SPAWN_DISTANCE)
		{
			keys.push_back(new Key(cx, cy));
			count++;
		}
	}
}

void Entity::spawnBot(Map* map, Player* player) {
	std::default_random_engine engine(int(time(0)));
	std::uniform_int_distribution dist(1, map->maze->size() - 2);

	const Coordinate& c = player->character->coord();
	while (true) {
		int x = dist(engine);
		int y = dist(engine);

		float cx = (x * Constant::SIZE) + Constant::SIZE / 2;
		float cy = (y * Constant::SIZE) + Constant::SIZE / 2;

		if (map->maze->cellType(y, x) == way &&
			(distance(cx, cy, c.x, c.y) > MIN_DISTANCE))
		{
			Bot* bot = new Bot(cx, cy);
			bots.push_back(bot);
			bot->pathFind(*(map->maze), player->character->coord());
			break;
		}
	}
}



/* -------------------------------------------------- */
// render
/* -------------------------------------------------- */
void Entity::render(SDL_Renderer* renderer, Camera* camera, const unsigned char& frame) const {

	SDL_Rect dest;
	dest.h = TILE_SIZE * camera->zoom;
	dest.w = (TILE_SIZE * camera->zoom);

	SDL_Rect src;
	src.h = TILE_SIZE;
	src.w = TILE_SIZE;
	src.x = (frame * TILE_SIZE);

	int halfWidth = Constant::SIZE / 2;

	// keys
	for (const auto& key : keys) {
		if (key == nullptr) continue;
		const Coordinate& k = key->coord();
		if (k.x + halfWidth < camera->start_x || k.x - halfWidth > camera->end_x ||
			k.y + halfWidth < camera->start_y || k.y - halfWidth > camera->end_y)
		{
			continue;
		}
		else {
			src.y = 0;
			dest.x = int((k.x - camera->start_x - halfWidth) * camera->zoom);
			dest.y = int((k.y - camera->start_y - halfWidth) * camera->zoom);
			SDL_RenderCopy(renderer, keySprite->sprite, &src, &dest);
		}
	}

	// bots
	for (const auto& bot : bots) {
		const Coordinate& k = bot->coord();
		if (k.x + halfWidth < camera->start_x || k.x - halfWidth > camera->end_x ||
			k.y + halfWidth < camera->start_y || k.y - halfWidth > camera->end_y)
		{
			continue;
		}
		else {
			src.y = bot->facing() * TILE_SIZE;
			dest.x = int((k.x - camera->start_x - halfWidth) * camera->zoom);
			dest.y = int((k.y - camera->start_y - halfWidth) * camera->zoom);
			SDL_RenderCopy(renderer, botSprite->sprite, &src, &dest);
		}
	}
}



/* -------------------------------------------------- */
// move
/* -------------------------------------------------- */
void Entity::moveBots(Map* map, Player* player, const float& deltaTime) {
	for (auto& bot : bots) {
		bot->move(*(map->maze), player->character->coord(), deltaTime);
	}
}