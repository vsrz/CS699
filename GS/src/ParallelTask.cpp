#include "ParallelTask.h"


ParallelTask::ParallelTask(State::Context context)
	: mFinished(false)
	, mThread(&ParallelTask::runTask, this)
	, mContext(context)
	, mCompletion(0.f)
	, mTasks(13.f)
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
	
	return mCompletion / mTasks;
}

void ParallelTask::runTask()
{

	mCompletion++;
	mContext.textures->load(Textures::StatusNotifiers, "res/notifiers_02.png");
	mContext.textures->load(Textures::Gracie, "res/gracie_manager.png");
	mCompletion++;
	mContext.textures->load(Textures::TestGuy, "res/TestGuy.png");
	mCompletion++;
	mContext.textures->load(Textures::WomanTeen01, "res/woman_teen_01.png");
	mCompletion++;
	mContext.textures->load(Textures::WomanMidage01, "res/woman_midage_01.png");
	mContext.textures->load(Textures::ManMidage01, "res/man_midage_01.png");
	mCompletion++;
	mContext.textures->load(Textures::ManYoung01, "res/man_young_01.png");
	mCompletion++;
	mContext.textures->load(Textures::ManTeen01, "res/man_teen_01.png");
	mCompletion++;
	mContext.textures->load(Textures::WomanOld01, "res/woman_old_01.png");
	mContext.textures->load(Textures::AutoDoors, "res/doors02.png");
	mCompletion++;
	mContext.textures->load(Textures::Kitty, "res/feline_01.png");
	mCompletion++;
	mContext.textures->load(Textures::AnimWash, "res/anim_wash_01.png");
	mContext.textures->load(Textures::GreenArrow, "res/arrow_green_01.png");
	mCompletion++;
	mContext.textures->load(Textures::AnimCut, "res/anim_cut_01.png");
	mCompletion++;
	mContext.textures->load(Textures::AnimColor, "res/anim_color_01.png");
	mCompletion++;
	mContext.textures->load(Textures::Hearts, "res/hearts_02.png");
	mCompletion++;
	mContext.textures->load(Textures::RedClick, "res/red_click.png");
	mContext.textures->load(Textures::GreenClick, "res/green_click.png");
	mCompletion = mTasks;

	// mFinished could be accessed from multiple threads
	{
		sf::Lock lock(mMutex);
		mFinished = true;
	}
}
