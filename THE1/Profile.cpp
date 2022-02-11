#include "Profile.h"

Profile::Profile(const std::string& email, const std::string& username, SubscriptionPlan plan) {
    this->email = email;
    this->username = username;
    this->plan = plan;
}

const std::string& Profile::getUsername() const {
    return this->username;
}

const std::string& Profile::getEmail() const {
    return this->email;
}

SubscriptionPlan Profile::getPlan() const {
    return this->plan;
}

LinkedList<Playlist>& Profile::getPlaylists() {
    return this->playlists;
}

LinkedList<Profile*>& Profile::getFollowings() {
    return this->following;
}

LinkedList<Profile*>& Profile::getFollowers() {
    return this->followers;
}

void Profile::setPlan(SubscriptionPlan plan) {
    this->plan = plan;
}

void Profile::followProfile(Profile* profile) {
    /* TODO */
    following.insertAtTheEnd(profile);
    profile->getFollowers().insertAtTheEnd(this);

}

void Profile::unfollowProfile(Profile* profile) {
    /* TODO */
    following.removeNode(profile);
    profile->getFollowers().removeNode(this);
}

void Profile::createPlaylist(const std::string& playlistName) {
    /* TODO */
    Playlist p(playlistName);
    playlists.insertAtTheEnd(p);
}

void Profile::deletePlaylist(int playlistId) {
    /* TODO */
    Node<Playlist>* temp = playlists.getFirstNode();
    int size = playlists.getSize();
    for (int i = 0; i < size; i++) {
        if (temp->data.getPlaylistId() == playlistId) {
            break;
        }
        else {
            temp = temp->next;
        }
    }
    temp->data.getSongs().removeAllNodes();
    playlists.removeNode(temp);
}

void Profile::addSongToPlaylist(Song* song, int playlistId) {
    /* TODO */
    Node<Playlist>* temp = playlists.getFirstNode();
    int size = playlists.getSize();
    for (int i = 0; i < size; i++) {
        if (temp->data.getPlaylistId() == playlistId) {
            break;
        }
        else {
            temp = temp->next;
        }
    }
    temp->data.addSong(song);

}

void Profile::deleteSongFromPlaylist(Song* song, int playlistId) {
    /* TODO */
    Node<Playlist>* temp = playlists.getFirstNode();
    int size = playlists.getSize();
    for (int i = 0; i < size; i++) {
        if (temp->data.getPlaylistId() == playlistId) {
            break;
        }
        else {
            temp = temp->next;
        }
    }
    temp->data.dropSong(song);

}

Playlist* Profile::getPlaylist(int playlistId) {
    /* TODO */
    Node<Playlist>* temp = playlists.getFirstNode();
    int size = playlists.getSize();
    for (int i = 0; i < size; i++) {
        if (temp->data.getPlaylistId() == playlistId) {
            break;
        }
        else {
            temp = temp->next;
        }
    }

    return &(temp->data);
}

LinkedList<Playlist*> Profile::getSharedPlaylists() {
    /* TODO */
    LinkedList<Playlist*> yeni;
    if (following.isEmpty()) {
        return yeni;
    }


    if (!following.isEmpty()) {
        Node<Profile*>* temp = following.getFirstNode();
        int size = following.getSize();
        for (int i = 0; i < size; i++) {
            Node<Playlist>* temp2 = temp->data->getPlaylists().getFirstNode();
            int size2 = (*temp).data->playlists.getSize();
            for (int j = 0; j < size2; j++) {
                if (temp2->data.isShared()) {
                    yeni.insertAtTheEnd(&(temp2->data));
                    temp2 = temp2->next;
                }
                else {
                    temp2 = temp2->next;
                }
            }
            temp = temp->next;
        }
    }
    return yeni;
}

void Profile::shufflePlaylist(int playlistId, int seed) {
    /* TODO */
    Node<Playlist>* temp = playlists.getFirstNode();
    int size = playlists.getSize();
    for (int i = 0; i < size; i++) {
        if (temp->data.getPlaylistId() == playlistId) {
            break;
        }
        else {
            temp = temp->next;
        }
    }
    temp->data.shuffle(seed);
}

void Profile::sharePlaylist(int playlistId) {
    /* TODO */
    Node<Playlist>* temp = playlists.getFirstNode();
    int size = playlists.getSize();
    for (int i = 0; i < size; i++) {
        if (temp->data.getPlaylistId() == playlistId) {
            break;
        }
        else {
            temp = temp->next;
        }
    }
    temp->data.setShared(true);

}

void Profile::unsharePlaylist(int playlistId) {
    /* TODO */
    Node<Playlist>* temp = playlists.getFirstNode();
    int size = playlists.getSize();
    for (int i = 0; i < size; i++) {
        if (temp->data.getPlaylistId() == playlistId) {
            break;
        }
        else {
            temp = temp->next;
        }
    }
    temp->data.setShared(false);
}

bool Profile::operator==(const Profile& rhs) const {
    return this->email == rhs.email && this->username == rhs.username && this->plan == rhs.plan;
}

bool Profile::operator!=(const Profile& rhs) const {
    return !(rhs == *this);
}

std::ostream& operator<<(std::ostream& os, const Profile& profile) {
    os << "email: " << profile.email << " |";
    os << " username: " << profile.username << " |";
    if (profile.plan == free_of_charge) {
        os << " plan: " << "free_of_charge" << " |";
    }
    else if (profile.plan == premium) {
        os << " plan: " << "premium" << " |";
    }
    else {
        os << " plan: " << "undefined" << " |";
    }

    os << " playlists: [";
    Node<Playlist>* firstPlaylistNode = profile.playlists.getFirstNode();
    Node<Playlist>* playlistNode = firstPlaylistNode;
    if (playlistNode) {
        do {
            os << playlistNode->data;
            if (playlistNode->next != firstPlaylistNode) os << ", ";
            playlistNode = playlistNode->next;
        } while (playlistNode != firstPlaylistNode);
    }
    os << "] |";
    os << " following: [";
    Node<Profile*>* firstProfileNode = profile.following.getFirstNode();
    Node<Profile*>* profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "] |";
    os << " followers: [";
    firstProfileNode = profile.followers.getFirstNode();
    profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "]";

    return os;
}
