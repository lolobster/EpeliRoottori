#include "AnimationManager.h"


AnimationManager::AnimationManager()
{
	timer.Start();
}

AnimationManager::~AnimationManager()
{
	frames.clear();
	delete anim;
}

void AnimationManager::LoadAnimation(const char *filename, const std::string& resourcePath) // Lataa animaation kuvatiedoston ja xml tiedoston avulla
{
	lodepng::load_file(anim_png, filename);
	unsigned error = lodepng::decode(animations, width, height, anim_png);
	if (error) // lataus ei onnistu --> virheilmotus
	{
		std::cout << "PNG load failed " << error << ": " << lodepng_error_text(error) << std::endl;
	}

	glGenTextures(1, &animID);
	glBindTexture(GL_TEXTURE_2D, animID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &animations[0]);
	glGenerateMipmap(GL_TEXTURE_2D);

	animations.clear();
	glBindTexture(GL_TEXTURE_2D, 0);

	//////////////////////////////////////////////////

	frameWidth = 0;
	frameHeight = 0;
	currentFrame.index = 0;
	loopable = false;

	// Lataa animaatiodatan
	rapidxml::xml_document<> document; // Animaatiodata dokumentti

	// Lukee tiedoston, asettaa datan ja sulkee tiedoston
	std::ifstream file(resourcePath);
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();

	std::string content(buffer.str());
	document.parse<0>(&content[0]);

	rapidxml::xml_node<>* root = document.first_node();

	// Luetaan framejen koko
	frameWidth = atoi(root->first_attribute("frameWidth")->value());
	frameHeight = atoi(root->first_attribute("frameHeight")->value());

	// Lasketaan framejen m‰‰r‰ rivi‰ kohden
	framesInARow = width / frameWidth;


	// Lukee framet
	for (rapidxml::xml_node<>* i = root->first_node("frame"); i; i = i->next_sibling())
	{
		Frame frame;
		frame.duration = static_cast<float>(atoi(i->first_attribute("duration")->value())) / 1000;
		index = atoi(i->first_attribute("id")->value());

		// Onko animaatio x vai y suuntainen?
		int horizontal = atoi(root->first_attribute("horizontal")->value());
		float texX = 0.0f;
		float texY = 0.0f;

		if (horizontal)
		{
			texX = static_cast<float>((index % framesInARow) * frameWidth);
			texY = static_cast<float>((index / framesInARow) * frameHeight);
		}
		else
		{
			texX = static_cast<float>((index / framesInARow) * frameHeight);
			texY = static_cast<float>((index % framesInARow) * frameWidth);
		}
		
		int loop = atoi(root->first_attribute("loopable")->value());
		
		if (loop == 1)
		{
			loopable = true;
		}

		// Laskee framen koordinaatit
		frame.texCoords.x = texX;
		frame.texCoords.y = texY;
		frame.texCoords.z = 0.0f;
		frame.texCoords.w = 0.0f;
		frame.index = index;
		index++;

		frames.push_back(frame);
	}
	// Indeksiss‰ on framejen m‰‰r‰
	rows = (index + 1) / framesInARow;
	columns = framesInARow;
	
	// Tyhj‰t‰‰n data
	content.clear();
	buffer.clear();
	document.clear();

	currentFrame = frames[0];
}

void AnimationManager::LoadAnimation(const char *filename, glm::vec2 frameSize, float frameDuration) // Vaihtoehtoinen tapa ladata animaatio. K‰ytt‰‰ hyv‰kseen kuvatiedostoa, yhden framen kokoa. Toisin kuin xml latauksen kanssa, kaikki framet n‰kyv‰t aina yht‰ kauan
{
	lodepng::load_file(anim_png, filename);
	unsigned error = lodepng::decode(animations, width, height, anim_png);
	if (error) // lataus ei onnistu --> virheilmotus
	{
		std::cout << "PNG load failed " << error << ": " << lodepng_error_text(error) << std::endl;
	}

	glGenTextures(1, &animID);
	glBindTexture(GL_TEXTURE_2D, animID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &animations[0]);
	glGenerateMipmap(GL_TEXTURE_2D);

	animations.clear();
	glBindTexture(GL_TEXTURE_2D, 0);

	// Ottaa vastaan yhden framen koon ja laskee sen perusteella kuinka monta riviin mahtuu
	frameWidth = frameSize.x;
	frameHeight = frameSize.y;
	framesInARow = width / frameWidth;
	currentFrame.index = 0;
	loopable = true;

	// Asettaa framejen tiedot vektoriin
	for (int i = 0; i < width / frameWidth * height / frameHeight; i++)
	{
		Frame frame;
		frame.duration = frameDuration;

		float texX = 0.0f;
		float texY = 0.0f;

		texX = static_cast<float>((index % framesInARow) * frameWidth);
		texY = static_cast<float>((index / framesInARow) * frameHeight);

		frame.texCoords.x = texX;
		frame.texCoords.y = texY;
		frame.texCoords.z = 0.0f;
		frame.texCoords.w = 0.0f;
		frame.index = index;
		index++;

		frames.push_back(frame);
	}
	rows = (index + 1) / framesInARow;
	columns = framesInARow;

	currentFrame = frames[0];
}

void AnimationManager::UpdateAnimation() // Hoitaa animaation p‰ivitt‰misen, siirtyy seuraavaan frameen halutun ajan kuluttua
{
	if (timer.GetGlobalTime() - timeElapsed > currentFrame.duration)
	{
		if (rows > 1)
		{
			if (currentFrame.index < frames.size() && currentFrame.index + 1 < frames.size())
			{
				currentFrame = frames[currentFrame.index + 1];
			}
			else if (currentFrame.index = frames.size() + 1 && loopable)
			{
				currentFrame = frames[0];
			}
		}
		else
		{
			if (currentFrame.index < frames.size() && currentFrame.index + 1 < frames.size())
			{
				currentFrame = frames[currentFrame.index + 1];
			}
			else if (currentFrame.index = frames.size() + 1 && loopable)
			{
				currentFrame = frames[0];
			}
			else
			{
				return;
			}
		}
		timeElapsed += timer.GetGlobalTime() - timeElapsed;
	}
}