#include "MusicStream.h"

#include <iostream>

void MusicStream::addProfile(const std::string& email, const std::string& username, SubscriptionPlan plan) {
    /* TODO */
    Profile profil(email, username, plan);
    profiles.insertAtTheEnd(profil);

}

void MusicStream::deleteProfile(const std::string& email) {
    /* TODO */
    int size = profiles.getSize();
    Node<Profile>* temp = profiles.getFirstNode();
    for (int i = 0; i < size; i++) {
        if (temp->data.getEmail() == email) {
            break;
        }
        temp = temp->next;
    }

    size = temp->data.getFollowings().getSize();
    Node<Profile*>* temp4;
    Node<Profile*>* temp2 = temp->data.getFollowings().getFirstNode();
    for (int i = 0; i < size; i++) {
        temp4 = temp2;
        temp2 = temp2->next;
        unfollowProfile(email, temp4->data->getEmail());

    }
    size = temp->data.getFollowers().getSize();
    temp2 = temp->data.getFollowers().getFirstNode();

    for (int i = 0; i < size; i++) {
        temp4 = temp2;
        temp2 = temp2->next;
        unfollowProfile(temp4->data->getEmail(), email);

    }
    size = temp->data.getPlaylists().getSize();
    Node<Playlist>* temp3 = temp->data.getPlaylists().getFirstNode();
    for (int i = 0; i < size; i++) {
        temp3->data.getSongs().removeAllNodes();
        temp3 = temp3->next;
    }
    temp->data.getPlaylists().~LinkedList();
    temp->data.getFollowers().~LinkedList();
    temp->data.getFollowings().~LinkedList();


    profiles.removeNode(temp);


}

void MusicStream::addArtist(const std::string& artistName) {
    /* TODO */
    Artist artist(artistName);
    artists.insertAtTheEnd(artist);
}

void MusicStream::addAlbum(const std::string& albumName, int artistId) {
    /* TODO */
    Album album(albumName);
    albums.insertAtTheEnd(album);
    int size = artists.getSize();
    Node<Artist>* temp = artists.getFirstNode();
    for (int i = 0; i < size; i++) {
        if (temp->data.getArtistId() == artistId) {

            break;
        }
        temp = temp->next;
    }

    temp->data.addAlbum(&(albums.getLastNode()->data));

}

void MusicStream::addSong(const std::string& songName, int songDuration, int albumId) {
    /* TODO */
    int size = albums.getSize();
    Song song(songName, songDuration);
    songs.insertAtTheEnd(song);
    Node<Album>* temp = albums.getFirstNode();
    for (int i = 0; i < size; i++) {
        if (temp->data.getAlbumId() == albumId) {

            break;
        }
        temp = temp->next;
    }
    temp->data.addSong(&(songs.getLastNode()->data));
}

void MusicStream::followProfile(const std::string& email1, const std::string& email2) {
    /* TODO */
    int size = profiles.getSize();
    Node<Profile>* temp = profiles.getFirstNode();
    Node<Profile>* temp2 = profiles.getFirstNode();
    for (int i = 0; i < size; i++) {
        if (temp->data.getEmail() == email1) {
            break;
        }
        temp = temp->next;
    }
    for (int i = 0; i < size; i++) {
        if (temp2->data.getEmail() == email2) {
            break;
        }
        temp2 = temp2->next;
    }
    temp->data.followProfile(&(temp2->data));
}

void MusicStream::unfollowProfile(const std::string& email1, const std::string& email2) {
    /* TODO */
    int size = profiles.getSize();
    Node<Profile>* temp = profiles.getFirstNode();
    Node<Profile>* temp2 = profiles.getFirstNode();
    for (int i = 0; i < size; i++) {
        if (temp->data.getEmail() == email1) {

        }
        else {
            temp = temp->next;
        }
        if (temp2->data.getEmail() == email2) {

        }
        else {
            temp2 = temp2->next;
        }
    }
    temp->data.unfollowProfile(&(temp2->data));
}

void MusicStream::createPlaylist(const std::string& email, const std::string& playlistName) {
    /* TODO */
    int size = profiles.getSize();
    Node<Profile>* temp = profiles.getFirstNode();

    for (int i = 0; i < size; i++) {
        if (temp->data.getEmail() == email) {
            break;
        }
        else {
            temp = temp->next;
        }
    }
    temp->data.createPlaylist(playlistName);
}

void MusicStream::deletePlaylist(const std::string& email, int playlistId) {
    /* TODO */
    int size = profiles.getSize();
    Node<Profile>* temp = profiles.getFirstNode();
    for (int i = 0; i < size; i++) {
        if (temp->data.getEmail() == email) {
            break;
        }
        else {
            temp = temp->next;
        }
    }
    temp->data.deletePlaylist(playlistId);

}

void MusicStream::addSongToPlaylist(const std::string& email, int songId, int playlistId) {
    /* TODO */
    int size = profiles.getSize();
    Node<Profile>* temp = profiles.getFirstNode();
    for (int i = 0; i < size; i++) {
        if (temp->data.getEmail() == email) {
            break;
        }
        else {
            temp = temp->next;
        }
    }

    int size2 = songs.getSize();
    Node<Song>* temp2 = songs.getFirstNode();
    for (int i = 0; i < size2; i++) {
        if (temp2->data.getSongId() == songId) {
            break;
        }
        temp2 = temp2->next;
    }
    temp->data.addSongToPlaylist(&(temp2->data), playlistId);
}

void MusicStream::deleteSongFromPlaylist(const std::string& email, int songId, int playlistId) {
    /* TODO */
    int size = profiles.getSize();
    Node<Profile>* temp = profiles.getFirstNode();
    for (int i = 0; i < size; i++) {
        if (temp->data.getEmail() == email) {
            break;
        }
        else {
            temp = temp->next;
        }
    }

    int size2 = songs.getSize();
    Node<Song>* temp2 = songs.getFirstNode();
    for (int i = 0; i < size2; i++) {
        if (temp2->data.getSongId() == songId) {
            break;
        }
        temp2 = temp2->next;
    }
    temp->data.deleteSongFromPlaylist(&(temp2->data), playlistId);
}

LinkedList<Song*> MusicStream::playPlaylist(const std::string& email, Playlist* playlist) {
    /* TODO */
    LinkedList<Song*> p;
    int size = profiles.getSize();
    Node<Profile>* temp = profiles.getFirstNode();
    for (int i = 0; i < size; i++) {
        if (temp->data.getEmail() == email) {
            break;
        }
        else {
            temp = temp->next;
        }
    }

    if (temp->data.getPlaylists().getNode(*playlist)) {
        if (temp->data.getPlan() == free_of_charge) {
            p = temp->data.getPlaylists().getNode(*playlist)->data.getSongs();
            p.insertAsEveryKthNode(&(Song::ADVERTISEMENT_SONG), 2);

        }
        else {
            p = temp->data.getPlaylists().getNode(*playlist)->data.getSongs();
        }
    }
    else {

        if (temp->data.getPlan() == free_of_charge) {
            p = temp->data.getSharedPlaylists().getNode(playlist)->data->getSongs();
            p.insertAsEveryKthNode(&(Song::ADVERTISEMENT_SONG), 2);

        }
        else {
            p = temp->data.getSharedPlaylists().getNode(playlist)->data->getSongs();
        }
    }

    return p;
}



Playlist* MusicStream::getPlaylist(const std::string& email, int playlistId) {
    /* TODO */
    int size = profiles.getSize();
    Node<Profile>* temp = profiles.getFirstNode();
    for (int i = 0; i < size; i++) {
        if (temp->data.getEmail() == email) {
            break;
        }
        else {
            temp = temp->next;
        }
    }
    return temp->data.getPlaylist(playlistId);
}

LinkedList<Playlist*> MusicStream::getSharedPlaylists(const std::string& email) {
    /* TODO */
    LinkedList<Playlist*> p;
    int size = profiles.getSize();
    Node<Profile>* temp = profiles.getFirstNode();
    for (int i = 0; i < size; i++) {
        if (temp->data.getEmail() == email) {
            break;
        }
        else {
            temp = temp->next;
        }
    }

    return temp->data.getSharedPlaylists();
}

void MusicStream::shufflePlaylist(const std::string& email, int playlistId, int seed) {
    /* TODO */
    int size = profiles.getSize();
    Node<Profile>* temp = profiles.getFirstNode();
    for (int i = 0; i < size; i++) {
        if (temp->data.getEmail() == email) {
            break;
        }
        else {
            temp = temp->next;
        }
    }
    temp->data.getPlaylist(playlistId)->shuffle(seed);
}

void MusicStream::sharePlaylist(const std::string& email, int playlistId) {
    /* TODO */
    int size = profiles.getSize();
    Node<Profile>* temp = profiles.getFirstNode();
    for (int i = 0; i < size; i++) {
        if (temp->data.getEmail() == email) {
            break;
        }
        else {
            temp = temp->next;
        }
    }
    temp->data.getPlaylist(playlistId)->setShared(true);
}

void MusicStream::unsharePlaylist(const std::string& email, int playlistId) {
    /* TODO */
    int size = profiles.getSize();
    Node<Profile>* temp = profiles.getFirstNode();
    for (int i = 0; i < size; i++) {
        if (temp->data.getEmail() == email) {
            break;
        }
        else {
            temp = temp->next;
        }
    }
    temp->data.getPlaylist(playlistId)->setShared(false);
}

void MusicStream::subscribePremium(const std::string& email) {
    /* TODO */
    int size = profiles.getSize();
    Node<Profile>* temp = profiles.getFirstNode();
    for (int i = 0; i < size; i++) {
        if (temp->data.getEmail() == email) {
            break;
        }
        else {
            temp = temp->next;
        }
    }
    temp->data.setPlan(premium);
}

void MusicStream::unsubscribePremium(const std::string& email) {
    /* TODO */
    int size = profiles.getSize();
    Node<Profile>* temp = profiles.getFirstNode();
    for (int i = 0; i < size; i++) {
        if (temp->data.getEmail() == email) {
            break;
        }
        else {
            temp = temp->next;
        }
    }
    temp->data.setPlan(free_of_charge);
}

void MusicStream::print() const {
    std::cout << "# Printing the music stream ..." << std::endl;

    std::cout << "# Number of profiles is " << this->profiles.getSize() << ":" << std::endl;
    this->profiles.print();

    std::cout << "# Number of artists is " << this->artists.getSize() << ":" << std::endl;
    this->artists.print();

    std::cout << "# Number of albums is " << this->albums.getSize() << ":" << std::endl;
    this->albums.print();

    std::cout << "# Number of songs is " << this->songs.getSize() << ":" << std::endl;
    this->songs.print();

    std::cout << "# Printing is done." << std::endl;
}
