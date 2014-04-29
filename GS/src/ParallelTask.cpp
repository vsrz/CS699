#include "ParallelTask.h"


ParallelTask::ParallelTask(State::Context context)
	: mFinished(false)
	, mThread(&ParallelTask::runTask, this)
	, mContext(context)
{

}

bool ParallelTask::isFinished()
{
	sf::Lock lock(mMutex);
	return mFinished;
}

void ParallelTask::execute()
{
	mFinished = false;
	mElapsedTime.restart();

	mThread.launch();

}

float ParallelTask::getCompletion()
{
	sf::Lock lock(mMutex);
	return mElapsedTime.getElapsedTime().asSeconds();
}

void ParallelTask::runTask()
{
	mContext.textures->load(Textures::StatusNotifiers, "res/notifiers_02.png");
	mContext.textures->load(Textures::TestGuy, "res/TestGuy.png");
	mContext.textures->load(Textures::WomanTeen01, "res/woman_teen_01.png");
	mContext.textures->load(Textures::WomanMidage01, "res/woman_midage_01.png");
	mContext.textures->load(Textures::WomanOld01, "res/woman_old_01.png");
	mContext.textures->load(Textures::ManYoung01, "res/man_young_01.png");
	mContext.textures->load(Textures::ManTeen01, "res/man_teen_01.png");
	mContext.textures->load(Textures::AutoDoors, "res/doors02.png");
	mContext.textures->load(Textures::Kitty, "res/feline_01.png");
	mContext.textures->load(Textures::AnimWash, "res/anim_wash_01.png");
	mContext.textures->load(Textures::AnimCut, "res/anim_cut_01.png");
	mContext.textures->load(Textures::AnimColor, "res/anim_color_01.png");
	mContext.textures->load(Textures::Hearts, "res/hearts_02.png");
	// mFinished could be accessed from multiple threads
	{
		sf::Lock lock(mMutex);
		mFinished = true;
	}

}
