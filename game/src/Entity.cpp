#include <random>

#include "Entity.h"


/* -------------------------------------------------- */
// constructor / destructor
/* -------------------------------------------------- */
Entity::Entity(SDL_Renderer* renderer) :
	keyTexture(new Texture()),
	botTexture(new Texture())
{
	keyTexture->load(renderer, KEY_PNG_PATH);
	botTexture->load(renderer, BOT_PNG_PATH);
}

Entity::~Entity() {
	delete keyTexture;
	keyTexture = nullptr;
	delete botTexture;
	botTexture = nullptr;
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
	return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}
const float Entity::distance(const Coordinate& c1, const Coordinate& c2) const {
	return sqrt(pow((c1.y - c2.y), 2) + pow((c1.y - c2.y), 2));
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
		if (map->maze->cellType(y, x) == way &&
			distance(x, y, p.x, p.y) > KEY_SPAWN_DISTANCE)
		{
			float cx = (x * Constant::SIZE) + Constant::SIZE / 2;
			float cy = (y * Constant::SIZE) + Constant::SIZE / 2;
			keys.push_back(new Key(cx, cy));
			count++;
		}
	}
}

void Entity::spawnBot(Map* map, Player* player) {
	std::default_random_engine engine(static_cast<int>(time(0)));
	std::uniform_int_distribution dist(1, map->maze->size() - 2);

	while (true) {
		int x = dist(engine);
		int y = dist(engine);
		const Coordinate& c = player->character->coord();
		if (map->maze->cellType(y, x) == way &&
			(distance(x, y, c.x, c.y) > MIN_DISTANCE))
		{
			float cx = (x * Constant::SIZE) + Constant::SIZE / 2;
			float cy = (y * Constant::SIZE) + Constant::SIZE / 2;
			bots.push_back(new Bot(cx, cy));
			bots.back()->pathFind(*(map->maze), player->character->coord());
			break;
		}
	}
}



/* -------------------------------------------------- */
// render
/* -------------------------------------------------- */
void Entity::render(SDL_Renderer* renderer, Camera* camera) const {

	SDL_Rect rect;
	rect.h = TILE_SIZE;
	rect.w = TILE_SIZE;

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
			rect.x = static_cast<int> (k.x - camera->start_x - halfWidth);
			rect.y = static_cast<int> (k.y - camera->start_y - halfWidth);
			SDL_RenderCopy(renderer, keyTexture->tex, nullptr, &rect);
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
			rect.x = static_cast<int> (k.x - camera->start_x - halfWidth);
			rect.y = static_cast<int> (k.y - camera->start_y - halfWidth);
			SDL_RenderCopy(renderer, botTexture->tex, nullptr, &rect);
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