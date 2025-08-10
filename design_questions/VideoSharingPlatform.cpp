#include <iostream>
#include <set>
#include <string> 
#include <map>
#include <random>
using namespace std;

// You have a video sharing platform where users can upload and delete videos. 
// Each video is a string of digits, where the ith digit of the string represents the
// content of the video at minute i. For example, the first digit represents the 
// content at minute 0 in the video, the second digit represents the content at 
// minute 1 in the video, and so on. Viewers of videos can also like and dislike 
// videos. Internally, the platform keeps track of the number of views, likes, and 
// dislikes on each video.

// When a video is uploaded, it is associated with the smallest available
// integer videoId starting from 0. Once a video is deleted, the videoId associated
// with that video can be reused for another video.

static const int MAX_VIDEOS = 1e5 + 2;

class Video {
    public:
    int videoId;
    string videoContent;
    int views=0;
    int likes=0;
    int dislikes=0;
    Video() : videoId(-1), videoContent(""), likes(0), dislikes(0), views(0) {} // default constructor

    Video(int videoId, string videoContent){
        this->videoId = videoId;
        this->videoContent = videoContent;
    }
};

// Id generator for video ids
// It returns the first unused video id
// Can handle upto 1e18 videos
class IdGenerator{ 
    set<int> emptySlots;
    // `ptr` is the next free id ignoring the ids freed after using. 
    long long ptr = 0;
public: 
    IdGenerator(){}

    int getNextId(){
        if(emptySlots.empty()){
            return ptr++;
        }  
        else{
            auto firstEmptySlot = emptySlots.begin();
            emptySlots.erase(firstEmptySlot);
            return *firstEmptySlot;
        }
    }

    void freeId(int videoId){
        emptySlots.insert(videoId);
    }

    bool isIdOccupied(int videoId){
        return !emptySlots.count(videoId) and ptr > videoId;
    }
};

// Singleton Class
class VideoSharingPlatform
{
private:
    static VideoSharingPlatform* instance;
    IdGenerator idGenerator;
    map<int, Video> videoGallery;

    // Private constructor to prevent direct instantiation
    VideoSharingPlatform(){
        idGenerator = IdGenerator();
    }

    // Delete copy constructor & assignment operator
    VideoSharingPlatform(const VideoSharingPlatform&) = delete;
    VideoSharingPlatform& operator=(const VideoSharingPlatform&) = delete;
public:

    static VideoSharingPlatform* getVideoSharingPlatform(){
        if(instance==nullptr){
            instance = new VideoSharingPlatform();
        }
        return instance;
    } 

    // The user uploads a video. Returns the videoId associated with the video.
    int uploadVideo(string videoContent){
        int id = idGenerator.getNextId();
        Video video = Video(id, videoContent);
        videoGallery[id] = video;
        return id;
    }

    //  If there is a video associated with videoId, remove the video.
   void deleteByVideoId(int videoId){
        if(idGenerator.isIdOccupied(videoId)){
            idGenerator.freeId(videoId);
            videoGallery.erase(videoId);
        }
   }

   // If there is a video associated with videoId, increase the number of views
   // on the video by 1 and return the substring of the video string starting at 
   // at the startMinute and ending at min(endMinute, video.length - 1) (inclusive). Otherwise, return "-1". 
   // startMinute and ending at
    string watch(int videoId, int startMinute, int endMinute){
        if(!videoGallery.count(videoId)){
            return "";
        }
        Video* searchedVideo = &videoGallery[videoId];
        searchedVideo->views++; 
        return searchedVideo->videoContent.substr(startMinute, endMinute - startMinute + 1);
    }

   void likeVideo(int videoId){
        if(!videoGallery.count(videoId)){
            return;
        }
        Video* searchedVideo = &videoGallery[videoId];
        searchedVideo->likes++; 
   }

   void dislikeVideo(int videoId){
        if(!videoGallery.count(videoId)){
            return;
        }
        Video* searchedVideo = &videoGallery[videoId];
        searchedVideo->dislikes++; 
   }

    std::vector<int> getLikesAndDislikes(int videoId) {
        if (!videoGallery.count(videoId)) {
            return {-1};
        }
        Video searchedVideo = videoGallery[videoId];
        return {searchedVideo.likes, searchedVideo.dislikes};
    }

    int getViews(int videoId){
        if(!videoGallery.count(videoId)){
            return -1;
        }
        Video searchedVideo = videoGallery[videoId];
        return searchedVideo.views;
    }
};

// Inside class → Declaration (just a promise it exists)
// Outside class → Definition (actual storage allocation)

// Define static member
VideoSharingPlatform* VideoSharingPlatform::instance = nullptr;

int main(){
    VideoSharingPlatform* hotstar = VideoSharingPlatform::getVideoSharingPlatform();
     // Operation 2: upload("123")
    hotstar->uploadVideo("123");

    // Operation 3: upload("456")
    hotstar->uploadVideo("456");

    // Operation 4: remove(4)
    hotstar->deleteByVideoId(4);

    // Operation 5: remove(0)
    hotstar->deleteByVideoId(0);

    // Operation 6: upload("789")
    hotstar->uploadVideo("789");

    // Operation 7: watch(1, 0, 5)
    cout<< hotstar->watch(1, 0, 5)<<endl;

    // Operation 8: watch(1, 0, 1)
    cout<<hotstar->watch(1, 0, 1)<<endl;

    // Operation 9: like(1)
    hotstar->likeVideo(1);

    // Operation 10: dislike(1)
    hotstar->dislikeVideo(1);

    // Operation 11: dislike(1)
    hotstar->dislikeVideo(1);

    // Operation 12: getLikesAndDislikes(1)
    {
        auto stats = hotstar->getLikesAndDislikes(1);
        cout << "Likes: " << stats[0] << ", Dislikes: " << stats[1] << endl;
    }

    // Operation 13: getViews(1)
    cout << "Views: " << hotstar->getViews(1) << endl;
    return 0;
}

